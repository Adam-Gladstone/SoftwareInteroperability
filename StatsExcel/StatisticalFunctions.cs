using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using StatsCLR;

namespace StatsExcel
{
    using ExcelDna.Integration;
    using ExcelDna.Integration.CustomUI;

    public static class StatisticalFunctions
    {
        //
        // DescriptiveStatistics
        //
        [ExcelFunction(Name = "StatisticalFunctions.DescriptiveStatistics",
                        Description = "Retrieve a package of descriptive statistics for the input data",
                        HelpTopic = "")]
        public static object[,] DescriptiveStatistics(
            [ExcelArgument(Description = "Array of data values")] double[] data,
            [ExcelArgument(Description = "Array of keys (optional)")] object[] keys
            )
        {
            object[,] obj = null;
            try
            {
                List<double> _data = new List<double>(data);
                List<string> _keys = Conversion.ConvertKeys(keys);

                Dictionary<string, double> results = Statistics.DescriptiveStatistics(_data, _keys);
                obj = Conversion.ResultsToObject(results);
            }
            catch(Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }

        //
        // LinearRegression
        //
        [ExcelFunction(Name = "StatisticalFunctions.LinearRegression",
                        Description = "Perform simple univariate linear regression: y ~ x, (where y = B0 + xB1)",
                        HelpTopic = "")]
        public static object[,] LinearRegression(
            [ExcelArgument(Description = "Array of xs (Independent variable)")] double[] xs,
            [ExcelArgument(Description = "Array of ys (Dependent variable)")] double[] ys
            )
        {
            object[,] obj = null;
            try
            {
                List<double> _xs = new List<double>(xs);
                List<double> _ys = new List<double>(ys);
                Dictionary<string, double> results = Statistics.LinearRegression(_xs, _ys);
                obj = Conversion.ResultsToObject(results);
            }
            catch (Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }

        //
        // T-test from summary input data
        //
        [ExcelFunction(Name = "StatisticalFunctions.SummaryDataTTest",
                        Description = "Perform a t-test from summary data.",
                        HelpTopic = "")]
        public static object[,] SummaryDataTTest(
            [ExcelArgument(Description = "Population mean: mu0")] double mu0,
            [ExcelArgument(Description = "Sample mean: x-bar")] double x_bar,
            [ExcelArgument(Description = "Sample standard deviation: sx")] double sx,
            [ExcelArgument(Description = "Sample size: n")] double n
            )
        {
            object[,] obj = null;
            try
            {
                TTest test = new TTest(mu0, x_bar, sx, n);
                test.Perform();

                Dictionary<string, double> results = test.Results();
                obj = Conversion.ResultsToObject(results);
            }
            catch (Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }

        //
        // One-sample t-test
        //
        [ExcelFunction(Name = "StatisticalFunctions.OneSampleTTest",
                        Description = "Perform a one-sample t-test.",
                        HelpTopic = "")]
        public static object[,] OneSampleTTest(
            [ExcelArgument(Description = "Population mean: mu0")] double mu0,
            [ExcelArgument(Description = "Array of data")] double[] x1
            )
        {
            object[,] obj = null;
            try
            {
                List<double> _x1 = new List<double>(x1);

                TTest test = new TTest(mu0, _x1);
                test.Perform();

                Dictionary<string, double> results = test.Results();
                obj = Conversion.ResultsToObject(results);
            }
            catch (Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }

        //
        // Two-sample t-test
        //
        [ExcelFunction(Name = "StatisticalFunctions.TwoSampleTTest",
                        Description = "Perform a two-sample t-test.",
                        HelpTopic = "")]
        public static object[,] TwoSampleTTest(
            [ExcelArgument(Description = "Array of data")] double[] x1,
            [ExcelArgument(Description = "Array of data")] double[] x2
            )
        {
            object[,] obj = null;
            try
            {
                List<double> _x1 = new List<double>(x1);
                List<double> _x2 = new List<double>(x2);

                TTest test = new TTest(_x1, _x2);
                test.Perform();

                Dictionary<string, double> results = test.Results();
                obj = Conversion.ResultsToObject(results);
            }
            catch (Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }

        //
        // Moving Average
        //
        [ExcelFunction(Name = "StatisticalFunctions.MovingAverage",
                        Description = "Compute a moving average from a set of data.",
                        HelpTopic = "")]
        public static object[,] MovingAverage(
            [ExcelArgument(Description = "Array of dates")] double[] dates,
            [ExcelArgument(Description = "Array of observations")] double[] observations,
            [ExcelArgument(Description = "Window")] int window
            )
        {
            object[,] obj = null;
            try
            {
                List<DateTime> _dates = Conversion.ToDateTime(dates);
                List<double> _observations = new List<double>(observations);

                TimeSeries ts = new TimeSeries(_dates, _observations);

                List<double> results = ts.MovingAverage(window);

                obj = Conversion.ResultsToObject(results);
            }
            catch (Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }

        //
        // Z-test from summary input data
        //
        [ExcelFunction(Name = "StatisticalFunctions.SummaryDataZTest",
                        Description = "Perform a z-test from summary data.",
                        HelpTopic = "")]
        public static object[,] ZTest(
            [ExcelArgument(Description = "Population mean: mu0")] double mu0,
            [ExcelArgument(Description = "Sample mean: x-bar")] double x_bar,
            [ExcelArgument(Description = "Sample standard deviation: sx")] double sx,
            [ExcelArgument(Description = "Sample size: n")] double n
            )
        {
            object[,] obj = null;
            try
            {
                ZTest test = new ZTest(mu0, x_bar, sx, n);
                test.Perform();

                Dictionary<string, double> results = test.Results();
                obj = Conversion.ResultsToObject(results);
            }
            catch (Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }

        //
        // One-sample z-test
        //
        [ExcelFunction(Name = "StatisticalFunctions.OneSampleZTest",
                        Description = "Perform a one-sample z-test.",
                        HelpTopic = "")]
        public static object[,] OneSampleZTest(
            [ExcelArgument(Description = "Population mean: mu0")] double mu0,
            [ExcelArgument(Description = "Array of data")] double[] x1
            )
        {
            object[,] obj = null;
            try
            {
                List<double> _x1 = new List<double>(x1);

                ZTest test = new ZTest(mu0, _x1);
                test.Perform();

                Dictionary<string, double> results = test.Results();
                obj = Conversion.ResultsToObject(results);
            }
            catch (Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }

        //
        // Two-sample z-test
        //
        [ExcelFunction(Name = "StatisticalFunctions.TwoSampleZTest",
                        Description = "Perform a two-sample z-test.",
                        HelpTopic = "")]
        public static object[,] TwoSampleZTest(
            [ExcelArgument(Description = "Array of data")] double[] x1,
            [ExcelArgument(Description = "Array of data")] double[] x2
            )
        {
            object[,] obj = null;
            try
            {
                List<double> _x1 = new List<double>(x1);
                List<double> _x2 = new List<double>(x2);

                ZTest test = new ZTest(_x1, _x2);
                test.Perform();

                Dictionary<string, double> results = test.Results();
                obj = Conversion.ResultsToObject(results);
            }
            catch (Exception e)
            {
                obj = Conversion.ReportException(e);
            }
            return obj;
        }
    }
}
