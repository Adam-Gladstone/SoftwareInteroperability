// StatisticalTests.cpp : Defines the functions for the entity.
//

#include <iostream>
#include <random>
#include <cmath>
#include <utility>

/*
* Including this file directly in a clr project and compiling with /clr or /clr:pure
* caused some issue: i.e. including / compiling boost inside a clr project did not work.
* However, wrapping it inside a C++ library seems to work fine: that is StatsCLR links against
* (static library) StatsLib which 'houses' the required boost functionality.
*/

#include <boost/math/statistics/t_test.hpp>
#include <boost/math/distributions/fisher_f.hpp>
#include <boost/math/statistics/z_test.hpp>

#include "StatisticalTests.h"
#include "DescriptiveStatistics.h"

namespace {

	//
	// Approximation to a normal CDF. Use for testing only.
	//
	auto normalCDF(double x) -> double
	{
		return std::erfc(-x / std::sqrt(2)) / 2;
	}
}

namespace StatisticsLibrary
{
	//
	// Retrieve the results
	//
	auto StatisticalTest::Results() const -> std::unordered_map<std::string, double>
	{
		return m_results;
	}

	//
	// T-Test
	//

	//
	// Summary data: population mean, sample mean, sample standard deviation, sample size.
	//
	TTest::TTest(double mu0, double x_bar, double sx, double n)
		: m_mu0(mu0)
		, m_x_bar(x_bar)
		, m_sx(sx)
		, m_n(n)
		, m_test_type(TestType::NoSample)
	{}

	//
	// One-sample: population mean, sample.
	//
	TTest::TTest(double mu0, std::vector<double> x1)
		: m_mu0(mu0)
		, m_x1(std::move(x1))
		, m_test_type(TestType::OneSample)
	{}

	//
	// Two-sample: the underlying boost implementation assumes equal variances
	//
	TTest::TTest(std::vector<double> x1, std::vector<double> x2)
		: m_x1(std::move(x1))
		, m_x2(std::move(x2))
		, m_test_type(TestType::TwoSample)
	{}

	//
	// Perform the t-test
	//
	auto TTest::Perform() -> bool
	{
		using namespace std::literals;
		bool result = false;

		if (m_test_type == TestType::NoSample || m_test_type == TestType::OneSample)
		{
			if (m_test_type == TestType::OneSample)
			{
				m_n = static_cast<double>(m_x1.size());
				m_x_bar = DescriptiveStatistics::Mean(m_x1);
				m_sx = DescriptiveStatistics::StandardDeviation(m_x1, DescriptiveStatistics::VarianceType::Sample);
			}

			const auto [t, p] = boost::math::statistics::one_sample_t_test(m_x_bar, m_sx * m_sx, m_n, m_mu0);

			m_results["t"s] = t;
			m_results["pval"s] = p;
			m_results["df"s] = m_n - 1.0;
			m_results["x1-bar"s] = m_x_bar;
			m_results["sx1"s] = m_sx;
			m_results["n1"s] = m_n;

			result = true;
		}
		else if (m_test_type == TestType::TwoSample)
		{
			const std::size_t n1 = m_x1.size();
			const std::size_t n2 = m_x2.size();
			const double df = (static_cast<double>(n1) + static_cast<double>(n2) - 2.0);

			const double mean1 = DescriptiveStatistics::Mean(m_x1);
			const double mean2 = DescriptiveStatistics::Mean(m_x2);
			const double sd1 = DescriptiveStatistics::StandardDeviation(m_x1, DescriptiveStatistics::VarianceType::Sample);
			const double  sd2 = DescriptiveStatistics::StandardDeviation(m_x2, DescriptiveStatistics::VarianceType::Sample);

			const auto [t, p] = boost::math::statistics::two_sample_t_test(m_x1, m_x2);

			m_results["t"s]	= t;
			m_results["pval"s]= p;
			m_results["df"s] = df;
			m_results["x1-bar"s] = mean1;
			m_results["sx1"s] = sd1;
			m_results["n1"s] = static_cast<double>(n1);
			m_results["x2-bar"s] = mean2;
			m_results["sx2"s] = sd2;
			m_results["n2"s] = static_cast<double>(n2);

			result = true;
		}

		return result;
	}

	//
	// F-Test
	//

	//
	// Summary data
	//
	FTest::FTest(double sx1, double sx2, double n1, double n2)
		: m_sx1(sx1)
		, m_sx2(sx2)
		, m_n1(n1)
		, m_n2(n2)
		, m_test_type(TestType::FromData)
	{}

	//
	// Two-sample
	//
	FTest::FTest(std::vector<double> x1, std::vector<double> x2)
		: m_x1(std::move(x1))
		, m_x2(std::move(x2))
		, m_test_type(TestType::TwoSample)
	{}

	//
	// Perform the F-test
	//
	auto FTest::Perform() -> bool
	{
		using namespace std::literals;
		bool result = false;
		if (m_test_type == TestType::Unknown) {
			return result;
		}

		if (m_test_type == TestType::TwoSample)
		{
			m_n1 = static_cast<double>(m_x1.size());
			m_n2 = static_cast<double>(m_x2.size());

			m_sx1 = DescriptiveStatistics::StandardDeviation(m_x1, DescriptiveStatistics::VarianceType::Sample);
			m_sx2 = DescriptiveStatistics::StandardDeviation(m_x2, DescriptiveStatistics::VarianceType::Sample);
		}

		// F-statistic:
		double F = (m_sx1 / m_sx2);
		F *= F;

		// Define our distribution, and get the probability:
		boost::math::fisher_f dist(m_n1 - 1, m_n2 - 1);

		const double cdf = boost::math::cdf(dist, F);
		// This is the area to the left of the F statistic in the F distribution (p(x<=F)).
		// We're interested in the area to the right of the F statistic, so in this case the p-value is 1 - cdf, and it is two-sided.
		const double p = (1 - cdf) * 2;

		const double alpha = 0.05;
		const double ucv = boost::math::quantile(boost::math::complement(dist, alpha));			// Upper Critical Value at alpha
		const double ucv2 = boost::math::quantile(boost::math::complement(dist, alpha / 2));	// Upper Critical Value at alpha/2
		const double lcv = boost::math::quantile(dist, alpha);									// Lower Critical Value at alpha
		const double lcv2 = boost::math::quantile(dist, alpha / 2);								// Lower Critical Value at alpha/2

		m_results["F"s] = F;
		m_results["cdf"s] = cdf;
		m_results["pval"s] = p;
		m_results["df1"s] = m_n1 - 1;
		m_results["sx1"s] = m_sx1;
		m_results["n1"s] = static_cast<double>(m_n1);
		m_results["df2"s] = m_n2 - 1;
		m_results["sx2"s] = m_sx2;
		m_results["n2"s] = static_cast<double>(m_n2);
		m_results["alpha"s] = alpha;
		m_results["ucv"s] = ucv;
		m_results["ucv2"s] = ucv2;
		m_results["lcv"s] = lcv;
		m_results["lcv2"s] = lcv2;
		result = true;

		return result;
	}

	//
	// Z-Test
	//
	// Summary data: population mean, sample mean, sample standard deviation, sample size.
	//
	ZTest::ZTest(double mu0, double x_bar, double sx, double n)
		: m_mu0(mu0)
		, m_x_bar(x_bar)
		, m_sx(sx)
		, m_n(n)
		, m_test_type(TestType::NoSample)
	{}

	//
	// One-sample: population mean, sample.
	//
	ZTest::ZTest(double mu0, std::vector<double> x1)
		: m_mu0(mu0)
		, m_x1(std::move(x1))
		, m_test_type(TestType::OneSample)
	{}

	//
	// Two-sample
	//
	ZTest::ZTest(std::vector<double> x1, std::vector<double> x2)
		: m_x1(std::move(x1))
		, m_x2(std::move(x2))
		, m_test_type(TestType::TwoSample)
	{}

	//
	// Perform the t-test
	//
	auto ZTest::Perform() -> bool
	{
		using namespace std::literals;
		bool result = false;

		boost::math::normal dist;

		if (m_test_type == TestType::NoSample || m_test_type == TestType::OneSample)
		{
			if (m_test_type == TestType::OneSample)
			{
				m_n = static_cast<double>(m_x1.size());
				m_x_bar = DescriptiveStatistics::Mean(m_x1);
				m_sx = DescriptiveStatistics::StandardDeviation(m_x1, DescriptiveStatistics::VarianceType::Sample);
			}

			const double t = (m_x_bar - m_mu0) / (m_sx / std::sqrt(m_n));
			const double p = 2.0 * boost::math::cdf(boost::math::complement(dist, t));

			m_results["z"s] = t;
			m_results["pval"s] = p;
			m_results["x1-bar"s] = m_x_bar;
			m_results["sx1"s] = m_sx;
			m_results["n1"s] = m_n;

			result = true;
		}
		else if (m_test_type == TestType::TwoSample)
		{
			const std::size_t n1 = m_x1.size();
			const std::size_t n2 = m_x2.size();

			const double mean1 = DescriptiveStatistics::Mean(m_x1);
			const double mean2 = DescriptiveStatistics::Mean(m_x2);
			const double sd1 = DescriptiveStatistics::StandardDeviation(m_x1, DescriptiveStatistics::VarianceType::Sample);
			const double sd2 = DescriptiveStatistics::StandardDeviation(m_x2, DescriptiveStatistics::VarianceType::Sample);

			const double t = (mean1 - mean2) / std::sqrt(((sd1 * sd1) / n1) + ((sd2 * sd2) / n2));
			const double p = 2.0 * boost::math::cdf(boost::math::complement(dist, t));

			m_results["z"s] = t;
			m_results["pval"s] = p;
			m_results["x1-bar"s] = mean1;
			m_results["sx1"s] = sd1;
			m_results["n1"s] = static_cast<double>(n1);
			m_results["x2-bar"s] = mean2;
			m_results["sx2"s] = sd2;
			m_results["n2"s] = static_cast<double>(n2);

			result = true;
		}

		return result;
	}

	//
	// One-way ANOVA Test
	//
	ANOVA::ANOVA(std::vector<double> x1, std::vector<double> x2, std::vector<double> x3)
		: m_x1(std::move(x1))
		, m_x2(std::move(x2))
		, m_x3(std::move(x3))
		, m_test_type(TestType::OneWay)
	{}

	//
	// Perform the ANOVA test
	//
	auto ANOVA::Perform() -> bool
	{
		using namespace std::literals;
		bool result = false;

		const double mean1 = DescriptiveStatistics::Mean(m_x1);
		const double mean2 = DescriptiveStatistics::Mean(m_x2);
		const double mean3 = DescriptiveStatistics::Mean(m_x3);

		const double total_mean = (mean1 + mean2 + mean3) / 3.0;

		double sst{ 0.0 };
		double ssw{ 0.0 };
		for (auto value : m_x1)	{
			ssw += (value - mean1) * (value - mean1);
			sst += (value - total_mean) * (value - total_mean);
		}

		for (auto value : m_x2) {
			ssw += (value - mean2) * (value - mean2);
			sst += (value - total_mean) * (value - total_mean);
		}

		for (auto value : m_x3) {
			ssw += (value - mean3) * (value - mean3);
			sst += (value - total_mean) * (value - total_mean);
		}

		// SSB – Sum of Squares Between Groups
		const double ssb = sst - ssw;

		// Degrees of freedom
		const std::size_t n_distict_groups = 3;
		const std::size_t df_ssb = n_distict_groups - 1;
		const std::size_t df_ssw = (m_x1.size() + m_x2.size() + m_x3.size()) - n_distict_groups;

		const double F = (ssb / df_ssb) / (ssw / df_ssw);

		// Define our distribution, and get the probability:
		boost::math::fisher_f dist(static_cast<double>(df_ssb), static_cast<double>(df_ssw));

		const double cdf = boost::math::cdf(dist, F);
		// This is the area to the left of the F statistic in the F distribution (p(x<=F)).
		// We're interested in the area to the right of the F statistic, so in this case the p-value is 1 - cdf.
		const double p = (1 - cdf);

		const double alpha = 0.05;
		const double ucv = boost::math::quantile(boost::math::complement(dist, alpha));			// Upper Critical Value at alpha
		const double lcv = boost::math::quantile(dist, alpha);									// Lower Critical Value at alpha

		m_results["F"s] = F;
		m_results["cdf"s] = cdf;
		m_results["pval"s] = p;
		m_results["df_ssb"s] = static_cast<double>(df_ssb);
		m_results["df_ssw"s] = static_cast<double>(df_ssw);
		m_results["ssb"s] = ssb;
		m_results["ssw"s] = ssw;
		m_results["sst"s] = sst;
		m_results["n1"s] = static_cast<double>(m_x1.size());
		m_results["n2"s] = static_cast<double>(m_x2.size());
		m_results["n3"s] = static_cast<double>(m_x3.size());
		m_results["alpha"s] = alpha;
		m_results["ucv"s] = ucv;
		m_results["lcv"s] = lcv;

		result = true;
		return result;
	}
}
