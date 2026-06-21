#pragma once

#include <string>
#include <map>
#include <unordered_map>


// Retrieve an error message if there is one
std::string getErrorReport();


namespace API
{
    // Retrieve a package of descriptive statistics for the input data
    std::map<std::string, double> DescriptiveStatistics(const std::vector<double>& data);

    // Retrieve the named descriptive statistics for the input data
    std::map<std::string, double> DescriptiveStatistics(const std::vector<double>& data, const std::vector<std::string>& keys);

    // Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
    std::map<std::string, double> LinearRegression(const std::vector<double>& xs, const std::vector<double>& ys);

    // Compute a simple moving average of size = window
    std::vector<double> MovingAverage(const std::vector<long>& dates, 
        const std::vector<double>& observations, const int window);

    // Summary data: population mean, sample mean, sample standard deviation, sample size.
    std::map<std::string, double> SummaryDataTTest(double mu0, double mean, double sd, double n);

    // One-sample: population mean, sample.
    std::map<std::string, double> OneSampleTTest(double mu0, const std::vector<double>& x1);

    // Two-sample
    std::map<std::string, double> TwoSampleTTest(const std::vector<double>& x1, const std::vector<double>& x2);

    // Summary data: population mean, sample mean, sample standard deviation, sample size.
    std::map<std::string, double> SummaryDataZTest(double mu0, double mean, double sd, double n);

    // One-sample: population mean, sample.
    std::map<std::string, double> OneSampleZTest(double mu0, const std::vector<double>& x1);

    // Two-sample
    std::map<std::string, double> TwoSampleZTest(const std::vector<double>& x1, const std::vector<double>& x2);
}