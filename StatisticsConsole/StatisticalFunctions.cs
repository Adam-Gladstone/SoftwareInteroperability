using StatisticsLibraryWRC;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StatisticsConsole
{
    internal class StatisticalFunctions
    {
        private static void DisplayDataSets(IList<object> dataSets)
        {
            Console.WriteLine("The data sets are:");
            foreach (var dataSet in dataSets)
            {
                DataSet _dataSet = (DataSet)dataSet;
                Console.WriteLine($"Name: {_dataSet.Name}\tElements: {_dataSet.Size}");
            }
            Console.WriteLine("");
        }

        private static void OutputResults(IDictionary<string, double> results)
        {
            foreach (var result in results)
            {
                Console.WriteLine(string.Format("{0}\t{1}", result.Key.ToString(), result.Value.ToString()));
            }
            Console.WriteLine("");
        }

        private static double GetValue(string key, IDictionary<string, double> results)
        {
            double value = 0;
            foreach (var result in results)
            {
                if(result.Key.ToString() == key)
                {
                    value = result.Value;
                    break;
                }
            }

            return value;
        }


        // Example session
        public static void Run()
        {
            Console.Clear();

            var statistics = new Statistics();
            var dataManager = new DataManager();

            List<double> xs = new List<double> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            List<double> ys = new List<double> { 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

            try
            {
                if (dataManager.Add("xs", xs))
                {
                    Console.WriteLine("Added data set \'{0}\' to the DataManager.", "xs");
                }

                if (dataManager.Add("ys", ys))
                {
                    Console.WriteLine("Added data set \'{0}\' to the DataManager.", "ys");
                }

                ulong count = dataManager.CountDataSets;
                Console.WriteLine(string.Format("There are: {0} data sets in the DataManager", count));

                IList<object> dataSets = dataManager.ListDataSets();
                DisplayDataSets(dataSets);

                {
                    Console.WriteLine("Descriptive Statistics for data set: xs");
                    IList<double> _xs = dataManager.GetDataSet("xs");
                    IList<string> keys = new List<string>();
                    keys.Add("Mean");
                    keys.Add("StdDev.S");

                    var results = statistics.DescriptiveStatistics(_xs, keys);
                    OutputResults(results);

                    results = statistics.DescriptiveStatistics(_xs);
                    OutputResults(results);
                }

                {
                    Console.WriteLine("Perform simple linear regression: y ~ x.");
                    IList<double> _xs = dataManager.GetDataSet("xs");
                    IList<double> _ys = dataManager.GetDataSet("ys");

                    var results = statistics.LinearRegression(_xs, _ys);
                    OutputResults(results);

                    Console.WriteLine("Estimated Coefficients:");
                    double b0 = GetValue("b0", results);
                    double b1 = GetValue("b1", results);

                    Console.WriteLine($"b0 = {b0:0.00}\nb1 = {b1:0.00}");
                    Console.WriteLine($"The formula is: y = {b0:0.00} + {b1:0.00}x");
                }

                {
                    Console.WriteLine("Perform a t-test using summary data.");
                    TTest test = new TTest(5, 9.261460, 0.2278881e-01, 195);
                    bool succeeded = test.Perform();
                    if (succeeded)
                    {
                        var results = test.Results();
                        OutputResults(results);
                    }
                }

                {
                    Console.WriteLine("Perform a two-sample t-test.");

                    IList<double> _x1 = dataManager.GetDataSet("xs");
                    IList<double> _x2 = dataManager.GetDataSet("ys");

                    IDictionary<string, IList<double>> data = new Dictionary<string, IList<double>>();
                    data["x1"] = _x1;
                    data["x2"] = _x2;
                    TTest test = new TTest(data);
                    bool succeeded = test.Perform();
                    if (succeeded)
                    {
                        var results = test.Results();
                        OutputResults(results);
                    }
                }

                count = dataManager.CountDataSets;
                Console.WriteLine($"There {(count != 1 ? " are " : " is ")}: {count} data sets in the DataManager.");

                dataSets = dataManager.ListDataSets();

                foreach(var dataSet in dataSets)
                {
                    string name = ((DataSet)dataSet).Name;
                    bool removed = dataManager.Remove(name);
                    if(removed)
                    {
                        Console.WriteLine(string.Format("Removed dataSet: {0}", name));

                        count = dataManager.CountDataSets;
                        Console.WriteLine(string.Format("There are now {0} data sets in the DataManager.", count));
                    }
                }
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            Console.WriteLine("Press any key to continue ...");
            Console.ReadKey();
        }
    }
}
