// StatisticalTests.cpp: defines the functions and class that we wrap

#include "pch.h"

#include "StatisticalTests.h"


namespace API
{
	namespace StatisticalTests
	{
        //
        boost::python::dict SummaryDataTTest(
            const boost::python::object& mu0,
            const boost::python::object& mean,
            const boost::python::object& sd,
            const boost::python::object& n
        )
        {
            double _mu0 = boost::python::extract<double>(mu0);
            double _mean = boost::python::extract<double>(mean);
            double _sd = boost::python::extract<double>(sd);
            double _n = boost::python::extract<double>(n);

            StatisticsLibrary::TTest test(_mu0, _mean, _sd, _n);
            [[maybe_unused]] const auto test_ok = test.Perform();

            const auto _results = test.Results();
            boost::python::dict results;
            Conversion::to_dict(_results, results);
            return results;
        }

        boost::python::dict OneSampleTTest(const boost::python::object& mu0, const boost::python::list& x1)
        {
            double _mu0 = boost::python::extract<double>(mu0);
            std::vector<double> _x1 = Conversion::to_std_vector<double>(x1);

            StatisticsLibrary::TTest test(_mu0, _x1);
            [[maybe_unused]] const auto test_ok = test.Perform();

            const auto _results = test.Results();
            boost::python::dict results;
            Conversion::to_dict(_results, results);
            return results;
        }

        boost::python::dict TwoSampleTTest(const boost::python::list& x1, const boost::python::list& x2)
        {
            std::vector<double> _x1 = Conversion::to_std_vector<double>(x1);
            std::vector<double> _x2 = Conversion::to_std_vector<double>(x2);

            StatisticsLibrary::TTest test(_x1, _x2);
            [[maybe_unused]] const auto test_ok = test.Perform();

            const auto _results = test.Results();
            boost::python::dict results;
            Conversion::to_dict(_results, results);
            return results;
        }

        boost::python::dict SummaryDataZTest(
            const boost::python::object& mu0,
            const boost::python::object& mean,
            const boost::python::object& sd,
            const boost::python::object& n
        )
        {
            double _mu0 = boost::python::extract<double>(mu0);
            double _mean = boost::python::extract<double>(mean);
            double _sd = boost::python::extract<double>(sd);
            double _n = boost::python::extract<double>(n);

            StatisticsLibrary::ZTest test(_mu0, _mean, _sd, _n);
            [[maybe_unused]] const auto test_ok = test.Perform();

            const auto _results = test.Results();
            boost::python::dict results;
            Conversion::to_dict(_results, results);
            return results;
        }

        boost::python::dict OneSampleZTest(const boost::python::object& mu0, const boost::python::list& x1)
        {
            double _mu0 = boost::python::extract<double>(mu0);
            std::vector<double> _x1 = Conversion::to_std_vector<double>(x1);

            StatisticsLibrary::ZTest test(_mu0, _x1);
            [[maybe_unused]] const auto test_ok = test.Perform();

            const auto _results = test.Results();
            boost::python::dict results;
            Conversion::to_dict(_results, results);
            return results;
        }

        boost::python::dict TwoSampleZTest(const boost::python::list& x1, const boost::python::list& x2)
        {
            std::vector<double> _x1 = Conversion::to_std_vector<double>(x1);
            std::vector<double> _x2 = Conversion::to_std_vector<double>(x2);

            StatisticsLibrary::ZTest test(_x1, _x2);
            [[maybe_unused]] const auto test_ok = test.Perform();

            const auto _results = test.Results();
            boost::python::dict results;
            Conversion::to_dict(_results, results);
            return results;
        }
	}
}
