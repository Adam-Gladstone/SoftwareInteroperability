// Functions.cpp: api functions
//
#include "Conversion.h"
#include "Functions.h"

#undef _USRDLL
#include "StatisticsLibrary.h"
#include "DescriptiveStatistics.h"
#include "DataManager.h"
#include "StatisticalTests.h"
#include "TimeSeries.h"
#define _USRDLL


//
// APIs
//
namespace API
{
    //
    // Retrieve a package of descriptive statistics for the input data
    //
    PyObject* DescriptiveStatistics(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY

        PyObject* data = nullptr;
        PyObject* keys = nullptr;

        if (!PyArg_ParseTuple(args, "O|O", &data, &keys)) {
            return nullptr;
        }

        std::vector<double> _data = Conversion::ObjectToVector(data);
        std::vector<std::string> _keys = Conversion::ObjectToStringVector(keys);

        std::unordered_map<std::string, double> results = StatisticsLibrary::GetDescriptiveStatistics(_data, _keys);
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)
    //
    PyObject* LinearRegression(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        PyObject* xs = nullptr;
        PyObject* ys = nullptr;

        if (!PyArg_ParseTuple(args, "OO", &xs, &ys)) {
            return nullptr;
        }

        std::vector<double> _xs = Conversion::ObjectToVector(xs);
        std::vector<double> _ys = Conversion::ObjectToVector(ys);
        std::unordered_map<std::string, double> results = StatisticsLibrary::LinearRegression(_xs, _ys);
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a t-test with summary data (no sample)
    //
    PyObject* SummaryDataTTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        double mu0{ 0.0 };
        double mean{ 0.0 };
        double sd{ 0.0 };
        double n{ 0.0 };

        if (!PyArg_ParseTuple(args, "dddd", &mu0, &mean, &sd, &n)) {
            return nullptr;
        }

        StatisticsLibrary::TTest test(mu0, mean, sd, n);
        [[maybe_unused]] const auto result = test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a one-sample t-test with population mean
    //
    PyObject* OneSampleTTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        double mu0{ 0.0 };
        PyObject* o = nullptr;

        if (!PyArg_ParseTuple(args, "dO", &mu0, &o)) {
            return nullptr;
        }

        std::vector<double> data = Conversion::ObjectToVector(o);

        StatisticsLibrary::TTest test(mu0, data);
        [[maybe_unused]] const auto test_ok = test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a two-sample t-test
    //
    PyObject* TwoSampleTTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        PyObject* x1 = nullptr;
        PyObject* x2 = nullptr;

        if (!PyArg_ParseTuple(args, "OO", &x1, &x2)) {
            return nullptr;
        }

        std::vector<double> _x1 = Conversion::ObjectToVector(x1);
        std::vector<double> _x2 = Conversion::ObjectToVector(x2);

        StatisticsLibrary::TTest test(_x1, _x2);
        [[maybe_unused]] const auto test_ok = test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a z-test with summary data (no sample)
    //
    PyObject* SummaryDataZTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        double mu0{ 0.0 };
        double mean{ 0.0 };
        double sd{ 0.0 };
        double n{ 0.0 };

        if (!PyArg_ParseTuple(args, "dddd", &mu0, &mean, &sd, &n)) {
            return nullptr;
        }

        StatisticsLibrary::ZTest test(mu0, mean, sd, n);
        [[maybe_unused]] const auto test_ok = test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a one-sample z-test with population mean
    //
    PyObject* OneSampleZTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        double mu0{ 0.0 };
        PyObject* o = nullptr;

        if (!PyArg_ParseTuple(args, "dO", &mu0, &o)) {
            return nullptr;
        }

        std::vector<double> data = Conversion::ObjectToVector(o);

        StatisticsLibrary::ZTest test(mu0, data);
        [[maybe_unused]] const auto test_ok = test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a two-sample z-test
    //
    PyObject* TwoSampleZTest(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        PyObject* x1 = nullptr;
        PyObject* x2 = nullptr;

        if (!PyArg_ParseTuple(args, "OO", &x1, &x2)) {
            return nullptr;
        }

        std::vector<double> _x1 = Conversion::ObjectToVector(x1);
        std::vector<double> _x2 = Conversion::ObjectToVector(x2);

        StatisticsLibrary::ZTest test(_x1, _x2);
        [[maybe_unused]] const auto test_ok = test.Perform();

        const auto results = test.Results();
        return Conversion::MapToObject(results);
        STATS_CATCH
    }

    //
    // Wrapper function for a time series moving average function
    //
    PyObject* MovingAverage(PyObject* /* unused module reference */, PyObject* args)
    {
        STATS_TRY
        PyObject* dates = nullptr;
        PyObject* observations = nullptr;
        long window{ 0 };

        if (!PyArg_ParseTuple(args, "OOl", &dates, &observations, &window)) {
            return nullptr;
        }

        std::vector<long> _dates = Conversion::ObjectToLongVector(dates);
        std::vector<double> _observations = Conversion::ObjectToVector(observations);

        StatisticsLibrary::TimeSeries ts(_dates, _observations);

        const auto results = ts.MovingAverage(window);
        return Conversion::VectorToObject(results);
        STATS_CATCH
    }
}
