#include <numeric>
#include <functional>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <stdexcept>
#include <map>
#include <cmath>

#include <boost/math/statistics/univariate_statistics.hpp>

#include "DescriptiveStatistics.h"

namespace {

	void check_empty_data(const std::vector<double>& data)
	{
		if (data.empty()) {
			throw std::invalid_argument("The data is empty.");
		}
	}

	void check_data_size(const std::vector<double>& data, std::size_t expected)
	{
		if (data.size() < expected) {
			throw std::invalid_argument("Insufficient data to perform the operation.");
		}
	}

	template <typename T>
	void check_input_range(const T& input, const T& min, const T& max)
	{
		if (input < min || input > max) {
			throw std::out_of_range("The input is out of range.");
		}
	}
}

namespace StatisticsLibrary::DescriptiveStatistics
{
	//
	// Compute the mean of a vector of values
	//
	auto Mean(const std::vector<double>& values) -> double
	{
		check_empty_data(values);

		const auto n = values.size();
		const auto sum = std::accumulate(std::begin(values), std::end(values), 0.0);
		const auto mean = sum / n;
		return mean;
	}

	//
	// Compute the trimmed mean of a vector of values
	//
	auto TrimmedMean(const std::vector<double>& values, double alpha) -> double
	{
		/*
		* https://www.gnu.org/software/gsl/doc/html/statistics.html
		* The trimmed mean, or truncated mean, discards a certain number of smallest and largest samples from the input vector 
		* before computing the mean of the remaining samples. The amount of trimming is specified by a factor 
		* alpha in the closed interval [0, 0.5]. Then the number of samples discarded from both ends of the input 
		* vector is alpha*n, where n is the length of the input. 
		* So to discard 25% of the samples from each end, one would set alpha = 0.25.
		*/

		constexpr auto min_alpha = 0.0;
		constexpr auto max_alpha = 0.5;
		check_empty_data(values);
		check_input_range(alpha, min_alpha, max_alpha);

		const auto size = values.size();
		std::vector<double> _values(values);
		std::sort(std::begin(_values), std::end(_values));

		auto low = static_cast<std::size_t>(size * alpha);
		auto high = size - low;
		if (low == high) {
			low--; high++;
		}

		const auto trimmed_size = size - (2 * low);
		const auto begin = _values.begin() + low;
		const auto end = _values.begin() + high;
		const auto sum = std::accumulate(begin, end, 0.0);
		const auto trimmed_mean = sum / trimmed_size;
		return trimmed_mean;
	}

	//
	// Compute the median of a vector of values
	//
	auto Median(const std::vector<double>& values) -> double
	{
		check_empty_data(values);

		const auto n = values.size();
		std::vector<double> _values(values);
		std::sort(std::begin(_values), std::end(_values));
		const auto mid = n / 2;
		return n % 2 == 0 ? (_values.at(mid) + _values.at(mid - 1)) / 2 : _values.at(mid);
	}

	//
	// Compute the specified quantile for a vector of values
	//
	auto Quantile(const std::vector<double>& values, double quantile) -> double
	{
		// https://www.open.edu/openlearn/science-maths-technology/prices-location-and-spread/content-section-3.2
		check_empty_data(values);

		const auto n = values.size();
		if (1 == n) { 
			return values[0];
		}

		std::vector<double> _values(values);
		std::sort(std::begin(_values), std::end(_values));

		const auto index = (n - 1) * quantile;
		const auto left = floor(index);
		const auto right = ceil(index);
		const auto weight = (index - left);
		// Interpolate
		const auto q = (1.0 - weight) * _values[static_cast<std::size_t>(left)] + weight * _values[static_cast<std::size_t>(right)];
		return q;
	}

	//
	// Compute the variance of a vector of values
	//
	auto Variance(const std::vector<double>& values, VarianceType type) -> double
	{
		check_empty_data(values);

		if (values.size() <= 1)	{
			return 0.0;
		}

		const auto n = (type == VarianceType::Population) ? values.size() : values.size() - 1;
		const auto mean = Mean(values);

		double sum_diff_sq{ 0.0 };
		for (auto value : values)
		{
			sum_diff_sq += (value - mean) * (value - mean);
		}

		const auto variance = sum_diff_sq / n;
		return variance;
	}

	//
	// Compute the standard deviation of a vector of values
	//
	auto StandardDeviation(const std::vector<double>& values, VarianceType type) -> double
	{
		const auto standard_deviation = std::sqrt(Variance(values, type));
		return standard_deviation;
	}

	//
	// Compute the standard error of a vector of values
	//
	auto StandardError(const std::vector<double>& values, VarianceType type) -> double
	{
		check_empty_data(values);

		const auto n = values.size();
		const auto standard_deviation = StandardDeviation(values, type);
		const auto standard_error = standard_deviation / std::sqrt(n);
		return standard_error;
	}

	//
	// Compute the skew of a vector of values
	//
	auto Skew(const std::vector<double>& values) -> double
	{
		check_data_size(values, 3);

		const double skew = boost::math::statistics::skewness(values);
		return skew;
	}

	//
	// Compute the kurtosis of a vector of values
	//
	auto Kurtosis(const std::vector<double>& values) -> double
	{
		// https://brownmath.com/stat/shape.htm
		check_data_size(values, 4);

		const double kurtosis = boost::math::statistics::kurtosis(values);
		return kurtosis;
	}

	//
	// Compute the excess kurtosis of a vector of values
	//
	auto ExcessKurtosis(const std::vector<double>& values) -> double
	{
		check_data_size(values, 4);

		const double kurtosis = boost::math::statistics::excess_kurtosis(values);
		return kurtosis;
	}

	//
	// Compute the range of a vector of values
	//
	auto Range(const std::vector<double>& values) -> double
	{
		check_empty_data(values);

		const auto [min, max] = std::minmax_element(std::begin(values), std::end(values));
		return (*max) - (*min);
	}

	//
	// Compute the minimum of a vector of values
	//
	auto Minimum(const std::vector<double>& values) -> double
	{
		check_empty_data(values);

		const auto [min, max] = std::minmax_element(std::begin(values), std::end(values));
		return *min;
	}

	//
	// Compute the maximum of a vector of values
	//
	auto Maximum(const std::vector<double>& values) -> double
	{
		check_empty_data(values);

		const auto [min, max] = std::minmax_element(std::begin(values), std::end(values));
		return *max;
	}

	//
	// Compute the sum of a vector of values
	//
	auto Sum(const std::vector<double>& values) -> double
	{
		const auto sum = std::accumulate(std::begin(values), std::end(values), 0.0);
		return sum;
	}

	//
	// Return the count of the values
	//
	auto Count(const std::vector<double>& values) -> std::size_t
	{
		return values.size();
	}

	//
	// Compute the product of a vector of values
	//
	auto Product(const std::vector<double>& values) -> double
	{
		check_empty_data(values);

		const auto product = std::accumulate(std::begin(values), std::end(values),
			1.0, std::multiplies<>());
		return product;
	}
}
