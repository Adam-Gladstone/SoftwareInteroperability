#pragma once

#undef _USRDLL
#include "..\..\Common\include\TimeSeries.h"
#define _USRDLL

#include "Conversion.h"


namespace API
{
    namespace TS
    {
        // TimeSeries wrapper class
        class TimeSeries final
        {
        public:
            // Destructor
            ~TimeSeries() = default;

            // Construct a time series from a vector of dates and observations
            TimeSeries(const boost::python::list& dates, const boost::python::list& observations);

            // Copy constructor
            TimeSeries(const TimeSeries& other) = default;

            // Copy assignment
            TimeSeries& operator=(const TimeSeries& other) = default;

            // Compute a simple moving average of size = window
            boost::python::list MovingAverage(const boost::python::object& window);

        private:
            StatisticsLibrary::TimeSeries m_ts;
        };
    }
}
