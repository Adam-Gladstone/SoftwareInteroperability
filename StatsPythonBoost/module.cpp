// module.cpp: defines the module that we are exposing to Python
#include "pch.h"

#include "Functions.h"
#include "StatisticalTests.h"
#include "DataManager.h"
#include "TimeSeries.h"

// Generate two function overloads for this function
BOOST_PYTHON_FUNCTION_OVERLOADS(f_overloads, API::DescriptiveStatistics, 1, 2)

BOOST_PYTHON_MODULE(StatsPythonBoost)
{
    using namespace boost::python;

    // Declare the functions that we are wrapping
    def("DescriptiveStatistics", API::DescriptiveStatistics, f_overloads(args("data", "keys"), 
        "Retrieve a package of descriptive statistics for the input data."));
    def("LinearRegression", API::LinearRegression, 
        "Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1).");
    def("MovingAverage", API::MovingAverage,
        "Compute a simple moving average of size = window.");

    def("SummaryDataTTest", API::StatisticalTests::SummaryDataTTest,
        "Summary data: population mean, sample mean, sample standard deviation, sample size.");
    def("OneSampleTTest", API::StatisticalTests::OneSampleTTest,
        "One-sample: population mean, sample.");
    def("TwoSampleTTest", API::StatisticalTests::TwoSampleTTest,
        "Two-sample: the underlying boost implementation assumes equal variances.");

    def("SummaryDataZTest", API::StatisticalTests::SummaryDataZTest,
        "Summary data: population mean, sample mean, sample standard deviation, sample size.");
    def("OneSampleZTest", API::StatisticalTests::OneSampleZTest,
        "One-sample: population mean, sample.");
    def("TwoSampleZTest", API::StatisticalTests::TwoSampleZTest,
        "Two-sample z-test.");

    // Declare the TTest class
    class_<API::StatisticalTests::StudentTTest>("TTest",
        init<const object&, const object&, const object&, const object&>(
            "Summary data: population mean, sample mean, sample standard deviation, sample size."))
        .def(init<const object&, const list&>("One - sample: population mean, sample."))
        .def(init<const list&, const list&>(
            "Two-sample: the underlying boost implementation assumes equal variances."))
        .def("Perform", &API::StatisticalTests::StudentTTest::Perform, "Perform the t-test.")
        .def("Results", &API::StatisticalTests::StudentTTest::Results, "Retrieve the results.")
    ;

    // Declare the ZTest class
    class_<API::StatisticalTests::ZTest>("ZTest",
        init<const object&, const object&, const object&, const object&>(
            "Summary data: population mean, sample mean, sample standard deviation, sample size."))
        .def(init<const object&, const list&>("One - sample: population mean, sample."))
        .def(init<const list&, const list&>(
            "Two-sample z-test."))
        .def("Perform", &API::StatisticalTests::ZTest::Perform, "Perform the z-test.")
        .def("Results", &API::StatisticalTests::ZTest::Results, "Retrieve the results.")
        ;

    // Declare the DataManager class
    class_<API::Data::DataManager>("DataManager",
        init<>("Default constructor."))
        .def("CountDataSets", &API::Data::DataManager::CountDataSets, 
            "Retrieve the number of data sets currently available.")
        .def("Add", &API::Data::DataManager::Add, 
            "Add the named data set to the collection.")
        .def("GetDataSet", &API::Data::DataManager::GetDataSet, 
            "Retrieve the named data set from the collection.")
        .def("ListDataSets", &API::Data::DataManager::ListDataSets, 
            "Retrieve the names of the data sets in the current collection.")
        .def("ClearDataSets", &API::Data::DataManager::ClearDataSets, 
            "Clear the data sets in the collection.")
        ;

    // Declare the TimeSeries class
    class_<API::TS::TimeSeries>("TimeSeries",
        init<const list&, const list&>("Construct a time series from a vector of dates and observations."))
        .def("MovingAverage", &API::TS::TimeSeries::MovingAverage,
            "Compute a simple moving average of size = window.")
        ;

}
