// Stats.cpp : Defines the functions for the library.
//

#include <iostream>
#include <string>
#include <string_view>
#include <map>
#include <functional>
#include <cmath>

#include "StatisticsLibrary.h"
#include "DescriptiveStatistics.h"

namespace {

	void check_same_size(const std::vector<double>& x, const std::vector<double>& y)
	{
		if (x.size() != y.size()) {
			throw std::invalid_argument("The datasets are different sizes.");
		}
	}
}

namespace StatisticsLibrary
{
	constexpr auto Q1 = 0.25;
	constexpr auto Q2 = 0.50;
	constexpr auto Q3 = 0.75;

	using namespace StatisticsLibrary::DescriptiveStatistics;
	//
	// Retrieve a package of descriptive statistics for the input data
	//
	auto
		GetDescriptiveStatistics(const std::vector<double>& data, const std::vector<std::string>& keys /* = std::vector<std::string>() */) -> std::unordered_map<std::string, double>
	{
		using namespace std::literals;
		using namespace StatisticsLibrary::DescriptiveStatistics;

		static const std::map<
			std::string_view, 
			std::function<double(const std::vector<double>& data)>
		> statistical_functions
		{
			{ "Mean"sv, Mean },
			{ "Median"sv,  Median },
			{
				"StdDev.P"sv, [](const std::vector<double>& data)
							{ return StandardDeviation(data, VarianceType::Population); }
			},
			{
				"StdDev.S"sv, [](const std::vector<double>& data)
							{ return StandardDeviation(data, VarianceType::Sample); }
			},
			{
				"StdErr"sv, [](const std::vector<double>& data)
							{ return StandardError(data, VarianceType::Sample); }
			},
			{
				"Variance.P"sv, [](const std::vector<double>& data)
							{ return Variance(data, VarianceType::Population); }
			},
			{
				"Variance.S"sv, [](const std::vector<double>& data)
							{ return Variance(data, VarianceType::Sample); }
			},
			{ "Skew"sv, Skew },
			{ "Kurtosis"sv, Kurtosis },
			{ "Kurtosis.XS"sv, ExcessKurtosis },
			{ "Range"sv, Range },
			{ "Minimum"sv, Minimum },
			{ "Maximum"sv, Maximum },
			{ "Sum"sv, Sum },
			{
				"Count"sv, [](const std::vector<double>& data)
						{ return static_cast<double>(Count(data)); }
			},
			{
				"Q1"sv, [](const std::vector<double>& data)
							{ return Quantile(data, Q1); }
			},
			{
				"Q2"sv, [](const std::vector<double>& data)
							{ return Quantile(data, Q2); }
			},
			{
				"Q3"sv, [](const std::vector<double>& data)
							{ return Quantile(data, Q3); }
			}
		};

		std::unordered_map<std::string, double> results;
		if (keys.empty())
		{
			for (const auto& statistic : statistical_functions)
			{
				std::string label(statistic.first);
				results[label] = statistic.second(data);
			}
		}
		else
		{
			// Retrieve the requested statistics
			for (const auto& key : keys)
			{
				// std::string key --> implicit conversion to string_view
				const auto& it = statistical_functions.find(key);
				if (it == statistical_functions.end())
				{
					std::string invalidKey("Invalid key: " + key);
					results[invalidKey] = 0.0;
				}
				else
				{
					const auto& f = it->second;
					results[key] = f(data);
				}
			}
		}

		return results;
	}

	//
	// Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
	//
	auto LinearRegression(const std::vector<double>& xs, const std::vector<double>& ys) -> std::unordered_map<std::string, double>
	{
		using namespace std::literals;
		using namespace StatisticsLibrary::DescriptiveStatistics;

		check_same_size(xs, ys);

		const double x_mean = Mean(xs);
		const double y_mean = Mean(ys);
		double ss_xy = 0;
		double ss_xx = 0;
		double ss_yy = 0;

		const std::size_t n = xs.size();

		for (std::size_t i = 0; i < n; ++i)
		{
			ss_xx += (xs[i] - x_mean) * (xs[i] - x_mean);
			ss_xy += (xs[i] - x_mean) * (ys[i] - y_mean);
			ss_yy += (ys[i] - y_mean) * (ys[i] - y_mean);
		}

		const double b1 = ss_xy / ss_xx;
		const double b0 = y_mean - b1 * x_mean;
		const double r = ss_xy / std::sqrt(ss_xx * ss_yy);
		const double r2 = r * r;

		std::unordered_map<std::string, double> results;

		results["x-mean"s] = x_mean;
		results["y-mean"s] = y_mean;
		results["SS_xx"s] = ss_xx;
		results["SS_xy"s] = ss_xy;
		results["SS_yy"s] = ss_yy;
		results["b0"s] = b0;
		results["b1"s] = b1;
		results["r"s] = r;
		results["r2"s] = r2;

		return results;
	}
}
