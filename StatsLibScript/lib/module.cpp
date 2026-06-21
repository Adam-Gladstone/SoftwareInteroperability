// module.cpp: defines the module that we are exposing to JavaScript

#include <emscripten/bind.h>

#include "../../Common/include/DescriptiveStatistics.h"
#include "../../Common/include/DataManager.h"
#include "../../Common/include/StatisticalTests.h"
#include "../../Common/include/TimeSeries.h"

// Proxy Classes
#include "Conversion.h"
#include "Functions.h"
#include "Classes.h"


using namespace emscripten;

//
// Return a version string
//
std::string getVersion() { return "6.0.0.0"; }

//
// Custom wrapper function that supports specifying the variance type
//
double StandardDeviation(const std::vector<double>& data, StatisticsLibrary::DescriptiveStatistics::VarianceType varType)
{
    return StatisticsLibrary::DescriptiveStatistics::StandardDeviation(data, varType);
}


EMSCRIPTEN_BINDINGS(my_module)
{
    register_vector<int>("VectorInt");
    register_vector<long>("VectorLong");
    register_vector<std::string>("VectorString");
    register_vector<double>("VectorDouble");
    register_map<std::string, double>("MapStringDouble");


    function("getVersion", &getVersion);
    
    function("getErrorReport", &getErrorReport);

    function("inputIntVector", optional_override([](emscripten::val value) {
                std::vector<int> vector = Conversion::to_vector<int>(value);
                Conversion::print<int>("IntVector", vector);
            }));
    function("inputDoubleVector", optional_override([](emscripten::val value) {
                std::vector<double> vector = Conversion::to_vector<double>(value);
                Conversion::print<double>("DoubleVector", vector);                
            }));
    function("inputStringVector", optional_override([](emscripten::val value) {
                std::vector<std::string> vector = Conversion::to_vector<std::string>(value);
                Conversion::print<std::string>("StringVector", vector);
            }));

    class_<API::Data::DataManager>("DataManager")
        .constructor()
        .function("CountDataSets", &API::Data::DataManager::CountDataSets)
        .function("Add", &API::Data::DataManager::Add)
        .function("GetDataSet", &API::Data::DataManager::GetDataSet)
        .function("ListDataSets", &API::Data::DataManager::ListDataSets)
        .function("ClearDataSets", &API::Data::DataManager::ClearDataSets);

    enum_<StatisticsLibrary::DescriptiveStatistics::VarianceType>("VarianceType")
        .value("Sample", StatisticsLibrary::DescriptiveStatistics::VarianceType::Sample)
        .value("Population", StatisticsLibrary::DescriptiveStatistics::VarianceType::Population);

    // Overloaded
    function("DescriptiveStatistics", select_overload<std::map<std::string, double>(const std::vector<double>&)>(&API::DescriptiveStatistics));
    function("DescriptiveStatistics", select_overload<std::map<std::string, double>(const std::vector<double>&, const std::vector<std::string>&)>(&API::DescriptiveStatistics));

    function("LinearRegression", &API::LinearRegression);
    function("MovingAverage", &API::MovingAverage);

    function("StandardDeviation", &StandardDeviation);

    function("SummaryDataTTest", &API::SummaryDataTTest);
    function("OneSampleTTest", &API::OneSampleTTest);
    function("TwoSampleTTest", &API::TwoSampleTTest);

    function("SummaryDataZTest", &API::SummaryDataZTest);
    function("OneSampleZTest", &API::OneSampleZTest);
    function("TwoSampleZTest", &API::TwoSampleZTest);

    // Declare the TTest class
    class_<API::StatisticalTests::TTest>("TTest")
        .constructor<double, double, double, double>()
        .constructor<const std::string&, double, const std::vector<double>&>()
        .constructor<const std::vector<double>&, const std::vector<double>&>()
        .function("Perform", &API::StatisticalTests::TTest::Perform)
        .function("Results", &API::StatisticalTests::TTest::Results);

    // Declare the ZTest class
    class_<API::StatisticalTests::ZTest>("ZTest")
        .constructor<double, double, double, double>()
        .constructor<const std::string&, double, const std::vector<double>&>()
        .constructor<const std::vector<double>&, const std::vector<double>&>()
        .function("Perform", &API::StatisticalTests::ZTest::Perform)
        .function("Results", &API::StatisticalTests::ZTest::Results);

    // Declare the TimeSeries class
    class_<StatisticsLibrary::TimeSeries>("TimeSeries")
        .constructor<const std::vector<long>&, const std::vector<double>&>()
        .function("MovingAverage", &StatisticsLibrary::TimeSeries::MovingAverage);
}