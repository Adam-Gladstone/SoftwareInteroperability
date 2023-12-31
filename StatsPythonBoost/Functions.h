#pragma once

#include <boost/python.hpp>

namespace API
{
    // Retrieve a package of descriptive statistics for the input data
    boost::python::dict DescriptiveStatistics(const boost::python::list& data, const boost::python::list& keys = boost::python::list());

    // Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
    boost::python::dict LinearRegression(const boost::python::list& xs, const boost::python::list& ys);

    // Compute a simple moving average of size = window
    boost::python::list MovingAverage(const boost::python::list& dates, 
        const boost::python::list& observations, const boost::python::object& window);
}