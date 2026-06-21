// Functions.cpp: defines the functions that we are wrapping

#include "../../Common/include/StatisticsLibrary.h"
#include "../../Common/include/TimeSeries.h"
#include "../../Common/include/StatisticalTests.h"

#include <map>

#include "Conversion.h"


//
// Class to store an exception message which can be 
// retrieved via the js layer
//
class ErrorReport final
{
    std::string error;

public:
    ErrorReport() = default;
    void set(const std::string& s) { error = s; }
    std::string get() const { return error.empty() ? "<No error report>" : error; }
};

// Global error report
static ErrorReport g_errorReport;

// Retrieve the error message
std::string getErrorReport() 
{ 
    return g_errorReport.get();
}


// Macros to simplify try/catch blocks
#define STATS_TRY try{

#define STATS_CATCH \
    }catch(const std::exception& e){  \
        g_errorReport.set(e.what());\
        throw;\
    }


namespace API
{
    //
    // Retrieve a package of descriptive statistics for the input data
    //
    std::map<std::string, double> DescriptiveStatistics(const std::vector<double>& data)
    {
        return Conversion::to_map(StatisticsLibrary::GetDescriptiveStatistics(data));
    }

    //
    // Retrieve the named package of descriptive statistics for the input data
    //
    std::map<std::string, double> DescriptiveStatistics(const std::vector<double>& data, const std::vector<std::string>& keys)
    {
        return Conversion::to_map(StatisticsLibrary::GetDescriptiveStatistics(data, keys));
    }

    //
    // Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
    //
    std::map<std::string, double> LinearRegression(const std::vector<double>& xs, const std::vector<double>& ys)
    {
        return Conversion::to_map(StatisticsLibrary::LinearRegression(xs, ys));
    }

    //
    // Compute a simple moving average of size = window
    //
    std::vector<double> MovingAverage(const std::vector<long>& dates, 
        const std::vector<double>& observations, const int window)
    {
        StatisticsLibrary::TimeSeries ts(dates, observations);

        return ts.MovingAverage(window);
    }

    std::map<std::string, double> SummaryDataTTest(double mu0, double mean, double sd, double n)
    {
        StatisticsLibrary::TTest test(mu0, mean, sd, n);

        [[maybe_unused]] const auto test_ok = test.Perform();

        return Conversion::to_map(test.Results());
    }

    std::map<std::string, double> OneSampleTTest(double mu0, const std::vector<double>& x1)
    {
        StatisticsLibrary::TTest test(mu0, x1);

        [[maybe_unused]] const auto test_ok = test.Perform();

        return Conversion::to_map(test.Results());
    }

    std::map<std::string, double> TwoSampleTTest(const std::vector<double>& x1, const std::vector<double>& x2)
    {
        StatisticsLibrary::TTest test(x1, x2);

        [[maybe_unused]] const auto test_ok = test.Perform();

        return Conversion::to_map(test.Results());
    }

    std::map<std::string, double> SummaryDataZTest(double mu0, double mean, double sd, double n)
    {
        StatisticsLibrary::ZTest test(mu0, mean, sd, n);

        [[maybe_unused]] const auto test_ok = test.Perform();

        return Conversion::to_map(test.Results());
    }

    std::map<std::string, double> OneSampleZTest(double mu0, const std::vector<double>& x1)
    {
        StatisticsLibrary::ZTest test(mu0, x1);

        [[maybe_unused]] const auto test_ok = test.Perform();

        return Conversion::to_map(test.Results());
    }

    std::map<std::string, double> TwoSampleZTest(const std::vector<double>& x1, const std::vector<double>& x2)
    {
        StatisticsLibrary::ZTest test(x1, x2);

        [[maybe_unused]] const auto test_ok = test.Perform();

        return Conversion::to_map(test.Results());
    }
}
