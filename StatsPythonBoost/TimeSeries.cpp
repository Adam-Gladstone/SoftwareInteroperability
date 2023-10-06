#include "pch.h"

#include "TimeSeries.h"

namespace API
{
    namespace TS
    {
        // Construct a time series from a vector of dates and observations
        TimeSeries::TimeSeries(const boost::python::list& dates, const boost::python::list& observations)
            : m_ts(Conversion::to_std_vector<long>(dates), Conversion::to_std_vector<double>(observations))
        {
        }

        // Compute a simple moving average of size = window
        boost::python::list TimeSeries::MovingAverage(const boost::python::object& window)
        {
            int _window = boost::python::extract<int>(window);
            const auto _results = m_ts.MovingAverage(_window);
            boost::python::list results;
            Conversion::to_list(_results, results);
            return results;
        }
    }
}