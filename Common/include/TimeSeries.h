#pragma once

#ifdef DYNAMIC
#   ifdef STATSDLL_EXPORTS
#       define STATSDLL_API __declspec(dllexport)
#   else
#       define STATSDLL_API __declspec(dllimport)
#   endif
#else
#   define STATSDLL_API
#endif

#ifdef _MSC_VER
#pragma warning( disable: 4251 ) // warning C4251: 'stl': class '...' needs to have dll-interface to be used by clients of class '...'
#endif

#include <vector>

namespace StatisticsLibrary
{
	using Date = long;

	class STATSDLL_API TimeSeries final
	{
    public:
        // Construction from vectors
		TimeSeries(std::vector<Date> dates, std::vector<double> observations);

        // Compute a simple moving average of size = window
        [[nodiscard]]
		std::vector<double> MovingAverage(std::size_t window) const;

    private:
        // Time series
        std::vector<Date> m_dates;
        std::vector<double> m_observations;
	};
}
