
// https://github.com/microsoft/onnxruntime/issues/9735
#define _STL_CRT_SECURE_INVALID_PARAMETER(expr) _CRT_SECURE_INVALID_PARAMETER(expr)

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>

#include "StatisticsLibrary.h"
#include "DescriptiveStatistics.h"
#include "StatisticalTests.h"
#include "DataManager.h"
#include "TimeSeries.h"

namespace py = pybind11;

//
// APIs
//
std::unordered_map<std::string, double> SummaryDataTTest(double mu0, double mean, double sd, double n)
{
    StatisticsLibrary::TTest test(mu0, mean, sd, n);
    [[maybe_unused]] const auto test_ok = test.Perform();

    return test.Results();
}

std::unordered_map<std::string, double> OneSampleTTest(double mu0, const std::vector<double>& data)
{
    StatisticsLibrary::TTest test(mu0, data);
    [[maybe_unused]] const auto test_ok = test.Perform();

    return test.Results();
}

std::unordered_map<std::string, double> TwoSampleTTest(const std::vector<double>& x1, const std::vector<double>& x2)
{
    StatisticsLibrary::TTest test(x1, x2);
    [[maybe_unused]] const auto test_ok = test.Perform();

    return test.Results();
}

//
// Wrapper functions for the z-test
//

std::unordered_map<std::string, double> SummaryDataZTest(double mu0, double mean, double sd, double n)
{
    StatisticsLibrary::ZTest test(mu0, mean, sd, n);
    [[maybe_unused]] const auto test_ok = test.Perform();

    return test.Results();
}

std::unordered_map<std::string, double> OneSampleZTest(double mu0, const std::vector<double>& data)
{
    StatisticsLibrary::ZTest test(mu0, data);
    [[maybe_unused]] const auto test_ok = test.Perform();

    return test.Results();
}

std::unordered_map<std::string, double> TwoSampleZTest(const std::vector<double>& x1, const std::vector<double>& x2)
{
    StatisticsLibrary::ZTest test(x1, x2);
    [[maybe_unused]] const auto test_ok = test.Perform();

    return test.Results();
}

std::vector<double> MovingAverage(const std::vector<long>& dates, const std::vector<double>& observations, int window)
{
    StatisticsLibrary::TimeSeries ts(dates, observations);
    const auto results = ts.MovingAverage(window);
    return results;
}

double SampleStandardDeviation(const std::vector<double>& data)
{
    using namespace StatisticsLibrary::DescriptiveStatistics;
    return StandardDeviation(data, VarianceType::Sample);
}

namespace {

    // Provide a string representation of this object
    std::string to_string(const StatisticsLibrary::DataManager& obj)
    {
        std::ostringstream out;
        std::vector<StatisticsLibrary::DataSetInfo> data_sets = obj.ListDataSets();
        if (!data_sets.empty())
        {
            for (std::size_t i = 0; i < data_sets.size(); ++i)
            {
                const auto& data_set = data_sets.at(i);
                out << "\n [" << i << "]\t" << data_set.first << " (count = " << data_set.second << ")";
            }
        }
        else
        {
            out << "There are no data sets available.";
        }
        return out.str();
    }

    // Provide a string representation of this object
    std::string to_string(const StatisticsLibrary::TimeSeries& obj)
    {
        std::ostringstream out;
        // Requires some access to the class internals
        out << "TimeSeries Data: dates and observations.";
        return out.str();
    }
}


//
// Module definition
//

PYBIND11_MODULE(StatsPythonPyBind, m) 
{
    m.def(  
        "DescriptiveStatistics", 
        &StatisticsLibrary::GetDescriptiveStatistics, py::arg("data"), py::arg("keys") = std::vector<std::string>(),
        R"pbdoc(Retrieve a package of descriptive statistics for the input data.)pbdoc"
    ).def(
        "LinearRegression",
        &StatisticsLibrary::LinearRegression,
        R"pbdoc(Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1).)pbdoc"
    ).def(
        "SummaryDataTTest",
        &SummaryDataTTest,
        R"pbdoc(No-sample: TTest from summary data.)pbdoc"
    ).def(
        "OneSampleTTest",
        &OneSampleTTest,
        R"pbdoc(One-sample: single unknown population mean m; the population standard deviation s is unknown.)pbdoc"
    ).def(
        "TwoSampleTTest",
        &TwoSampleTTest,
        R"pbdoc(Two-sample: the underlying boost implementation assumes equal variances.)pbdoc"
    ).def(
        "SummaryDataZTest",
        &SummaryDataZTest,
        R"pbdoc(No-sample: ZTest from summary data.)pbdoc"
    ).def(
        "OneSampleZTest",
        &OneSampleZTest,
        R"pbdoc(One-sample: single unknown population mean m; the population standard deviation s is unknown.)pbdoc"
    ).def(
        "TwoSampleZTest",
        &TwoSampleZTest,
        R"pbdoc(Two-sample z-test.)pbdoc"
    ).def(
        "MovingAverage",
        &MovingAverage,
        R"pbdoc(Compute a simple moving average of size = window.)pbdoc"
    ).def(
        "Mean",
        &StatisticsLibrary::DescriptiveStatistics::Mean,
        R"pbdoc(Compute the mean of the data.)pbdoc"
    ).def(
        "StdDev",
        &StatisticsLibrary::DescriptiveStatistics::StandardDeviation,
        py::arg("data"), py::arg("VarianceType"),
        R"pbdoc(Compute the standard deviation of the data.)pbdoc"
    ).def(
        "StdDevS",
        &SampleStandardDeviation,
        R"pbdoc(Compute the standard deviation of the data.)pbdoc"
    )
        ;

    py::enum_<StatisticsLibrary::DescriptiveStatistics::VarianceType>(m, "VarianceType")
        .value("Sample", StatisticsLibrary::DescriptiveStatistics::VarianceType::Sample)
        .value("Population", StatisticsLibrary::DescriptiveStatistics::VarianceType::Population)
        ;

    // This is the underlying TTest class; no wrapper required
    py::class_<StatisticsLibrary::TTest>(m, "TTest")
        .def(py::init<double, double, double, double>(), "Summary data: population mean, sample mean, sample standard deviation, sample size.")
        .def(py::init<double, const std::vector<double>& >(), "One-sample: population mean, sample.")
        .def(py::init<const std::vector<double>&, const std::vector<double>& >(), "Two-sample: the underlying boost implementation assumes equal variances.")
        .def("Perform", &StatisticsLibrary::TTest::Perform, "Perform the t-test.")
        .def("Results", &StatisticsLibrary::TTest::Results, "Retrieve the results.")
        .def("__repr__",
            [](const StatisticsLibrary::TTest&) {
                return "<example.TTest>";
            }
    );

    // This is the underlying ZTest class; no wrapper required
    py::class_<StatisticsLibrary::ZTest>(m, "ZTest")
        .def(py::init<double, double, double, double>(), "Summary data: population mean, sample mean, sample standard deviation, sample size.")
        .def(py::init<double, const std::vector<double>& >(), "One-sample: population mean, sample.")
        .def(py::init<const std::vector<double>&, const std::vector<double>& >(), "Two-sample z-test.")
        .def("Perform", &StatisticsLibrary::ZTest::Perform, "Perform the z-test.")
        .def("Results", &StatisticsLibrary::ZTest::Results, "Retrieve the results.")
        .def("__repr__",
            [](const StatisticsLibrary::ZTest& a) {
                return "<example.ZTest>";
            }
    );

    // This is the underlying DataManager class; no wrapper required
    py::class_<StatisticsLibrary::DataManager>(m, "DataManager")
        .def(py::init<>(), "Default constructor.")
        .def("CountDataSets", &StatisticsLibrary::DataManager::CountDataSets, "Retrieve the number of data sets currently available.")
        .def("Add", &StatisticsLibrary::DataManager::Add, "Add the named data set to the collection.")
        .def("GetDataSet", &StatisticsLibrary::DataManager::GetDataSet, "Retrieve the named data set from the collection.")
        .def("ListDataSets", &StatisticsLibrary::DataManager::ListDataSets, "Retrieve the names of the data sets in the current collection.")
        .def("ClearDataSets", &StatisticsLibrary::DataManager::ClearDataSets, "Clear the data sets in the collection.")
        .def("__repr__",
            [](const StatisticsLibrary::DataManager& a) {
                return "<DataManager> containing: " + to_string(a);
            }
    );

    // This is the underlying TimeSeries class; no wrapper required
    py::class_<StatisticsLibrary::TimeSeries>(m, "TimeSeries")
        .def(py::init<const std::vector<long>&, const std::vector<double>&>(), 
            "Construct a time series from a vector of dates and observations.")
        .def("MovingAverage", &StatisticsLibrary::TimeSeries::MovingAverage, "Compute a simple moving average of size = window.")
        .def("__repr__",
            [](const StatisticsLibrary::TimeSeries& a) {
                return "<TimeSeries> containing: " + to_string(a);
            }
    );


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
