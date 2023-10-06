// TimeSeries.cpp : Defines the functions for the entity.
//

#undef min

#include <stdexcept>
#include <cmath>
#include <utility>

#include "TimeSeries.h"

namespace StatisticsLibrary
{
	//
	// Construction from vectors
	//
	TimeSeries::TimeSeries(std::vector<Date> dates, std::vector<double> observations)
		: m_dates(std::move(dates))
		, m_observations(std::move(observations))
	{
		if (m_dates.size() != m_observations.size())
		{
			throw std::length_error("There must be the same number of dates and observations.");
		}
	}

	//
	// Compute a simple moving average of size = window
	//
	auto TimeSeries::MovingAverage(std::size_t window) const -> std::vector<double>
	{
		const std::size_t size = m_observations.size();
		if (window <= 1 || window > size)
		{
			throw std::logic_error("The window size must be greater than 1 and less than the number of observations.");
		}

		std::vector<double> result(size, 0.0);
		double sum = 0;
		for (std::size_t i = 0; i < size; ++i)
		{
			sum += m_observations[i];
			if (i >= window)
			{
				sum -= m_observations[i - window];
			}

			if (i < window - 1)
			{
				result[i] = NAN;
			}
			else
			{
				result[i] = sum / std::min(i + 1, window);
			}
		}
		return result;
	}
}
