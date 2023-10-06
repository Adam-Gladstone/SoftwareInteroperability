using System;
using System.Collections.Generic;
using System.Linq;

using Microsoft.VisualStudio.TestTools.UnitTesting;


namespace StatsCLR.UnitTests
{
    [TestClass]
    public class UnitTests
    {
        [TestMethod]
        public void TestDescriptiveStatistics()
        {
            // Arrange
            List<double> xs = new List<double> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            List<string> keys = new List<string>();

            // Act
            Dictionary<string, double> results = Statistics.DescriptiveStatistics(xs, keys);

            // Assert
            Assert.AreEqual(4.5, results["Mean"]);
            Assert.AreEqual(4.5, results["Median"]);
            Assert.AreEqual(9, results["Range"]);
            Assert.AreEqual(2.872281, results["StdDev.P"], 1e-6);
            Assert.AreEqual(3.027650, results["StdDev.S"], 1e-6);
            Assert.AreEqual(1.77575757, results["Kurtosis"], 1e-6);
            Assert.AreEqual(-1.2242424, results["Kurtosis.XS"], 1e-6);
            Assert.AreEqual(0.957427, results["StdErr"], 1e-6);
            Assert.AreEqual(9.166666, results["Variance.S"], 1e-6);
            Assert.AreEqual(8.250000, results["Variance.P"], 1e-6);
            Assert.AreEqual(0, results["Skew"]);
            Assert.AreEqual(0, results["Minimum"]);
            Assert.AreEqual(9, results["Maximum"]);
            Assert.AreEqual(45, results["Sum"]);
            Assert.AreEqual(10, results["Count"]);
            Assert.AreEqual(2.25, results["Q1"]);
            Assert.AreEqual(6.75, results["Q3"]);
        }

        [TestMethod]
        public void TestLinearRegression()
        {
            // Arrange
            List<double> xs = new List<double> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            List<double> ys = new List<double> { 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

            // Act
            Dictionary<string, double> results = Statistics.LinearRegression(xs, ys);

            // Assert
            Assert.AreEqual(1.2363636, results["b0"], 1e-6);
            Assert.AreEqual(1.1696969, results["b1"], 1e-6);
            Assert.AreEqual(0.9759805523748860, results["r"], 1e-14);
            Assert.AreEqual(0.9525380386139880, results["r2"], 1e-14);
        }

        [TestMethod]
        [ExpectedException(typeof(InvalidOperationException))]
        public void TestDescriptiveStatisticsThrows()
        {
            // Arrange
            List<double> xs = null;//new List<double>();
            List<string> keys = new List<string>();

            // Act
            Dictionary<string, double> results = Statistics.DescriptiveStatistics(xs, keys);
            //Assert.ThrowsException<InvalidOperationException>(() => Statistics.DescriptiveStatistics(xs));
        }

        [TestMethod]
        [ExpectedException(typeof(InvalidOperationException))]
        public void TestLinearRegressionThrows()
        {
            // Arrange
            List<double> xs = new List<double>();
            List<double> ys = new List<double>();

            // Act
            Dictionary<string, double> results = Statistics.LinearRegression(xs, ys);
        }

        [TestMethod]
        public void TestSmmaryDataTTest()
        {
            // Arrange
            TTest test = new TTest(5, 9.261460, 0.2278881e-01, 195);

            // Act
            bool result = test.Perform();
            var results = test.Results();

            // Assert
            Assert.AreEqual(result, true);
            Assert.AreEqual(results["t"], 2611.28380, 1e-5);
            Assert.AreEqual(results["pval"], 0.000e+000, 1e-14);
            Assert.AreEqual(results["df"], 194.0);
            Assert.AreEqual(results["x1-bar"], 9.26146, 1e-5);
            Assert.AreEqual(results["sx1"], 0.02279, 1e-5);
            Assert.AreEqual(results["n1"], 195);
        }

        [TestMethod]
        public void TestOneSampleTTest()
        {
            // Arrange 
            List<double> weight = new List<double> { 17.6, 20.6, 22.2, 15.3, 20.9, 21.0, 18.9, 18.9, 18.9, 18.2 };
            TTest test = new TTest(25.0, weight);

            // Act
            bool result = test.Perform();
            var results = test.Results();

            // Assert
            Assert.AreEqual(result, true);
            Assert.AreEqual(results["t"], -9.0783, 1e-4);
            Assert.AreEqual(results["pval"], 7.9531e-06, 1e-6);
            Assert.AreEqual(results["df"], 9.0);
            Assert.AreEqual(results["x1-bar"], 19.25, 1e-2);
            Assert.AreEqual(results["sx1"], 2.00291, 1e-5);
            Assert.AreEqual(results["n1"], 10);
        }

        [TestMethod]
        public void TestTwoSampleTTest()
        {
            // Arrange
            List<double> us_data = new List<double> { 
                                                        18, 15, 18, 16, 17, 15, 14, 14, 14, 15, 15, 14, 15, 14, 22, 18, 21, 21, 10, 10, 
                                                        11, 9,  28, 25, 19, 16, 17, 19, 18, 14, 14, 14, 14, 12, 13, 13, 18, 22, 19, 18, 
                                                        23, 26, 25, 20, 21, 13, 14, 15, 14, 17, 11, 13, 12, 13, 15, 13, 13, 14, 22, 28, 
                                                        13, 14, 13, 14, 15, 12, 13, 13, 14, 13, 12, 13, 18, 16, 18, 18, 23, 11, 12, 13, 
                                                        12, 18, 21, 19, 21, 15, 16, 15, 11, 20, 21, 19, 15, 26, 25, 16, 16, 18, 16, 13, 
                                                        14, 14, 14, 28, 19, 18, 15, 15, 16, 15, 16, 14, 17, 16, 15, 18, 21, 20, 13, 23, 
                                                        20, 23, 18, 19, 25, 26, 18, 16, 16, 15, 22, 22, 24, 23, 29, 25, 20, 18, 19, 18, 
                                                        27, 13, 17, 13, 13, 13, 30, 26, 18, 17, 16, 15, 18, 21, 19, 19, 16, 16, 16, 16, 
                                                        25, 26, 31, 34, 36, 20, 19, 20, 19, 21, 20, 25, 21, 19, 21, 21, 19, 18, 19, 18, 
                                                        18, 18, 30, 31, 23, 24, 22, 20, 22, 20, 21, 17, 18, 17, 18, 17, 16, 19, 19, 36, 
                                                        27, 23, 24, 34, 35, 28, 29, 27, 34, 32, 28, 26, 24, 19, 28, 24, 27, 27, 26, 24, 
                                                        30, 39, 35, 34, 30, 22, 27, 20, 18, 28, 27, 34, 31, 29, 27, 24, 23, 38, 36, 25, 
                                                        38, 26, 22, 36, 27, 27, 32, 28, 31 
                                                    };
            List<double> jp_data = new List<double> {   
                                                        24, 27, 27, 25, 31, 35, 24, 19, 28, 23, 27, 20, 22, 18, 20, 31, 32, 31, 32, 24, 
                                                        26, 29, 24, 24, 33, 33, 32, 28, 19, 32, 34, 26, 30, 22, 22, 33, 39, 36, 28, 27, 
                                                        21, 24, 30, 34, 32, 38, 37, 30, 31, 37, 32, 47, 41, 45, 34, 33, 24, 32, 39, 35, 
                                                        32, 37, 38, 34, 34, 32, 33, 32, 25, 24, 37, 31, 36, 36, 34, 38, 32, 38, 32 
                                                    };

            TTest test = new TTest(us_data, jp_data);

            // Act
            bool result = test.Perform();
            var results = test.Results();

            // Assert
            Assert.AreEqual(result, true);
            Assert.AreEqual(results["t"], -12.62059, 1e-5);
            Assert.AreEqual(results["pval"], 5.273e-030, 1e-14);
            Assert.AreEqual(results["df"], 326.0);
            Assert.AreEqual(results["x1-bar"], 20.14458, 1e-5);
            Assert.AreEqual(results["sx1"], 6.41470, 1e-5);
            Assert.AreEqual(results["n1"], 249);
            Assert.AreEqual(results["x2-bar"], 30.48101, 1e-5);
            Assert.AreEqual(results["sx2"], 6.10771, 1e-5);
            Assert.AreEqual(results["n2"], 79);
        }

        [TestMethod]
        public void TestDataManagerCount()
        {
            // Arrange
            DataManager manager = new DataManager();
            List<double> xs = new List<double>(){ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            List<double> ys = new List<double>() { 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

            manager.ClearDataSets();
            manager.Add("xs", xs);
            manager.Add("ys", ys);

            // Act
            ulong count = manager.CountDataSets();

            // Assert
            Assert.AreEqual(count, (ulong)2);
        }

        [TestMethod]
        public void TestDataManagerAdd()
        {
            // Arrange
            DataManager manager = new DataManager();
            List<double> xs = new List<double>() { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            manager.ClearDataSets();
            manager.Add("xs", xs);

            // Act
            ulong count = manager.CountDataSets();

            // Assert
            Assert.AreEqual(count, (ulong)1);
        }

        [TestMethod]
        [ExpectedException(typeof(InvalidOperationException))]
        public void TestDataManagerAddEmptyName()
        {
            // Arrange
            DataManager manager = new DataManager();
            List<double> xs = new List<double>() { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            manager.ClearDataSets();

            // Act
            manager.Add("", xs);
        }

        [TestMethod]
        [ExpectedException(typeof(InvalidOperationException))]
        public void TestDataManagerAddEmptyData()
        {
            // Arrange
            DataManager manager = new DataManager();
            List<double> xs = new List<double>(){ };

            manager.ClearDataSets();

            // Act
            manager.Add("xs", xs);
        }

        [TestMethod]
        public void TestDataManagerList()
        {
            // Arrange
            DataManager manager = new DataManager();
            List<double> xs = new List<double>() { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            List<double> ys = new List<double>() { 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

            manager.ClearDataSets();
            manager.Add("xs", xs);
            manager.Add("ys", ys);

            // Act
            var dataSets = manager.ListDataSets();

            // Assert
            foreach(var dataSet in dataSets)
	        {
                List<double> data = manager.GetDataSet(dataSet.Item1);
                Assert.AreEqual((ulong)data.Count, dataSet.Item2);
            }
        }

        [TestMethod]
        public void TestMovingAverage()
        {
            // Arrange
            List<double> ts = new List<double>() { 1, 3, 5, 7, 8, 18, 4, 1, 4, 3, 5, 7, 5, 6, 7 };
            List<DateTime> dt = new List<DateTime>() { new DateTime(1), new DateTime(2), new DateTime(3), new DateTime(4), 
                                                        new DateTime(5), new DateTime(6), new DateTime(7), new DateTime(8),
                                                        new DateTime(9), new DateTime(10), new DateTime(11), new DateTime(12), 
                                                        new DateTime(13), new DateTime(14), new DateTime(15) };

            TimeSeries time_series = new TimeSeries(dt, ts);

            // Act
            List<double> results = time_series.MovingAverage(3);

            // Assert
            Assert.IsTrue(Double.IsNaN(results[0]));
            Assert.IsTrue(Double.IsNaN(results[1]));
            Assert.AreEqual(3, results[2], 1e-5);
            Assert.AreEqual(5, results[3], 1e-5);
            Assert.AreEqual(6.66667, results[4], 1e-5);
            Assert.AreEqual(11, results[5], 1e-5);
            Assert.AreEqual(10, results[6], 1e-5);
            Assert.AreEqual(7.66667, results[7], 1e-5);
            Assert.AreEqual(3, results[8], 1e-5);
            Assert.AreEqual(2.66667, results[9], 1e-5);
            Assert.AreEqual(4, results[10], 1e-5);
            Assert.AreEqual(5, results[11], 1e-5);
            Assert.AreEqual(5.66667, results[12], 1e-5);
            Assert.AreEqual(6, results[13], 1e-5);
            Assert.AreEqual(6, results[14], 1e-5);
        }

        [TestMethod]
        public void TestSmmaryDataZTest()
        {
            // Arrange
            ZTest test = new ZTest(5, 6.7, 7.1, 29);

            // Act
            bool result = test.Perform();
            var results = test.Results();

            // Assert
            Assert.AreEqual(result, true);
            Assert.AreEqual(results["z"], 1.2894056580462898, 1e-14);
            Assert.AreEqual(results["pval"], 0.19725709541241010, 1e-14);
            Assert.AreEqual(results["x1-bar"], 6.7, 1e-5);
            Assert.AreEqual(results["sx1"], 7.1, 1e-5);
            Assert.AreEqual(results["n1"], 29);
        }

        [TestMethod]
        public void TestOneSampleZTest()
        {
            // Arrange 
            List<double> x = new List<double>() { 3, 7, 11, 0, 7, 0, 4, 5, 6, 2 };
            ZTest test = new ZTest(3.0, x);

            // Act
            bool result = test.Perform();
            var results = test.Results();

            // Assert
            Assert.AreEqual(result, true);
            Assert.AreEqual(results["z"], 1.3789156793307651, 1e-14);
            Assert.AreEqual(results["pval"], 0.16792075329459241, 1e-14);
            Assert.AreEqual(results["x1-bar"], 4.5, 1e-14);
            Assert.AreEqual(results["sx1"], 3.4399612400917157, 1e-14);
            Assert.AreEqual(results["n1"], 10);
        }

        [TestMethod]
        public void TestTwoSampleZTest()
        {
            // Arrange
            List<double> x = new List<double>() { 7.8, 6.6, 6.5, 7.4, 7.3, 7.0, 6.4, 7.1, 6.7, 7.6, 6.8 };
            List<double> y = new List<double>() { 4.5, 5.4, 6.1, 6.1, 5.4, 5.0, 4.1, 5.5 };

            ZTest test = new ZTest(x, y);

            // Act
            bool result = test.Perform();
            var results = test.Results();

            // Assert
            Assert.AreEqual(result, true);
            Assert.AreEqual(results["z"], 6.1280815146654328, 1e-14);
            Assert.AreEqual(results["pval"], 8.8945016827014375e-10, 1e-10);
            Assert.AreEqual(results["x1-bar"], 7.0181818181818167, 1e-14);
            Assert.AreEqual(results["sx1"], 0.46436662631627990, 1e-14);
            Assert.AreEqual(results["n1"], 11);
            Assert.AreEqual(results["x2-bar"], 5.2625000000000002, 1e-14);
            Assert.AreEqual(results["sx2"], 0.70698050084244091, 1e-14);
            Assert.AreEqual(results["n2"], 8);
        }
    }
}
