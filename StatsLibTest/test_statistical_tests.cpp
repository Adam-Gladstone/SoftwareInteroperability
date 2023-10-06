#include "pch.h"

#include "DescriptiveStatistics.h"
#include "StatisticalTests.h"
#include "DataManager.h"

using namespace StatisticsLibrary;
using namespace StatsLibTest::Utils;

TEST(StatisticalTests, SummaryDataTTest)
{
	// Arrange
	TTest statistical_test(5, 9.261460, 0.2278881e-01, 195);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("t"), 2611.28380, 1e-5);
	EXPECT_NEAR(results.at("pval"), 0.000e+000, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("df"), 194.0);
	EXPECT_NEAR(results.at("x1-bar"), 9.26146, 1e-5);
	EXPECT_NEAR(results.at("sx1"), 0.02279, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n1"), 195);
}

TEST(StatisticalTests, OneSampleTTest)
{
	// Arrange
	const std::string weight_data = testSettings.GetDataDirectory() + "\\weight.txt";

	std::vector<double> x1 = ReadData(weight_data);

	TTest statistical_test(25.0, x1);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("t"), -9.0783, 1e-4);
	EXPECT_NEAR(results.at("pval"), 7.9531e-06, 1e-6);
	EXPECT_DOUBLE_EQ(results.at("df"), 9.0);
	EXPECT_NEAR(results.at("x1-bar"), 19.25, 1e-2);
	EXPECT_NEAR(results.at("sx1"), 2.00291, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n1"), 10);
}

TEST(StatisticalTests, OneSampleTTestNoData)
{
	// Arrange
	std::vector<double> x1{ };

	TTest statistical_test(25.0, x1);

	// Act / Assert
	EXPECT_THROW([[maybe_unused]] const auto result = statistical_test.Perform(), std::invalid_argument);

	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(results.size(), 0);
}

TEST(StatisticalTests, TwoSampleTTest)
{
	// Arrange
	const std::string jp_data = testSettings.GetDataDirectory() + "\\jp-mpg.txt";
	const std::string us_data = testSettings.GetDataDirectory() + "\\us-mpg.txt";

	std::vector<double> x1 = ReadData(us_data);
	std::vector<double> x2 = ReadData(jp_data);

	TTest statistical_test(x1, x2);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("t"), -12.62059, 1e-5);
	EXPECT_NEAR(results.at("pval"), 5.273e-030, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("df"), 326.0);
	EXPECT_NEAR(results.at("x1-bar"), 20.14458, 1e-5);
	EXPECT_NEAR(results.at("sx1"), 6.41470, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n1"), 249);
	EXPECT_NEAR(results.at("x2-bar"), 30.48101, 1e-5);
	EXPECT_NEAR(results.at("sx2"), 6.10771, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n2"), 79);
}

//
// https://www.boost.org/doc/libs/1_77_0/libs/math/example/f_test.cpp
//
TEST(StatisticalTests, SummaryDataFTestA)
{
	// Arrange
	FTest statistical_test(65.54909, 61.85425, 240, 240);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("F"), 1.12304, 1e-5);
	EXPECT_NEAR(results.at("cdf"), 0.8148, 1e-5);
	EXPECT_NEAR(results.at("pval"), 0.370383, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("df1"), 239.0);
	EXPECT_NEAR(results.at("sx1"), 65.54909, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n1"), 240);
	EXPECT_DOUBLE_EQ(results.at("df2"), 239.0);
	EXPECT_NEAR(results.at("sx2"), 61.85425, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n2"), 240);
}

//
// https://www.boost.org/doc/libs/1_77_0/libs/math/example/f_test.cpp
//
TEST(StatisticalTests, SummaryDataFTestB)
{
	// Arrange
	FTest statistical_test(4.9082, 2.5874, 11, 9);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("F"), 3.59847, 1e-5);
	EXPECT_NEAR(results.at("cdf"), 0.958856, 1e-5);
	EXPECT_NEAR(results.at("pval"), 0.082288, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("df1"), 10);
	EXPECT_NEAR(results.at("sx1"), 4.9082, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n1"), 11);
	EXPECT_DOUBLE_EQ(results.at("df2"), 8);
	EXPECT_NEAR(results.at("sx2"), 2.5874, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n2"), 9);
}

//
// https://www.geeksforgeeks.org/fishers-f-test-in-r-programming/
//
TEST(StatisticalTests, TwoSampleFTestA)
{
	using namespace StatisticsLibrary::DescriptiveStatistics;
	// Arrange
	std::vector<double> x1{ 16, 17, 25, 26, 32, 34, 38, 40, 42 };
	std::vector<double> x2{ 600, 590, 590, 630, 610, 630 };

	FTest statistical_test(x1, x2);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("F"), 0.2725248, 1e-5);
	EXPECT_NEAR(results.at("cdf"), 0.0506081, 1e-5);
	EXPECT_NEAR(results.at("pval"), 1.898783, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("df1"), 8);
	EXPECT_NEAR(results.at("sx1"), StandardDeviation(x1, VarianceType::Sample), 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n1"), 9);
	EXPECT_DOUBLE_EQ(results.at("df2"), 5);
	EXPECT_NEAR(results.at("sx2"), StandardDeviation(x2, VarianceType::Sample), 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n2"), 6);
}

//
// https://www.geeksforgeeks.org/fishers-f-test-in-r-programming/
//
TEST(StatisticalTests, TwoSampleFTestB)
{
	using namespace StatisticsLibrary::DescriptiveStatistics;
	// Arrange
	std::vector<double> x1{ 25, 29, 35, 46, 58, 66, 68 };
	std::vector<double> x2{ 14, 16, 24, 28, 32, 35, 37, 42, 43, 45, 47 };

	FTest statistical_test(x1, x2);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("F"), 2.4081, 1e-5);
	EXPECT_NEAR(results.at("cdf"), 0.894750, 1e-5);
	EXPECT_NEAR(results.at("pval"), 0.210499, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("df1"), 6);
	EXPECT_NEAR(results.at("sx1"), StandardDeviation(x1, VarianceType::Sample), 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n1"), 7);
	EXPECT_DOUBLE_EQ(results.at("df2"), 10);
	EXPECT_NEAR(results.at("sx2"), StandardDeviation(x2, VarianceType::Sample), 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n2"), 11);
}

TEST(StatisticalTests, SummaryDataZTest)
{
	//
	// https://www.statisticshowto.com/one-sample-z-test/
	//

	// Arrange
	ZTest statistical_test(5, 6.7, 7.1, 29);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("z"), 1.2894056580462898, 1e-14);
	EXPECT_NEAR(results.at("pval"), 0.19725709541241010, 1e-14);
	EXPECT_NEAR(results.at("x1-bar"), 6.7, 1e-5);
	EXPECT_NEAR(results.at("sx1"), 7.1, 1e-5);
	EXPECT_DOUBLE_EQ(results.at("n1"), 29);
}

TEST(StatisticalTests, OneSampleZTest)
{
	//
	// https://cran.r-project.org/web/packages/distributions3/vignettes/one-sample-z-test.html
	//

	// Arrange
	std::vector<double> x1{ 3,7,11,0,7,0,4,5,6,2 };

	ZTest statistical_test(3.0, x1);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("z"), 1.3789156793307651, 1e-14);
	EXPECT_NEAR(results.at("pval"), 0.16792075329459241, 1e-14);
	EXPECT_NEAR(results.at("x1-bar"), 4.5, 1e-14);
	EXPECT_NEAR(results.at("sx1"), 3.4399612400917157, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("n1"), 10);
}

TEST(StatisticalTests, TwoSampleZTest)
{
	//
	// https://www.rdocumentation.org/packages/BSDA/versions/1.2.0/topics/z.test
	//

	// Arrange
	std::vector<double> x{ 7.8, 6.6, 6.5, 7.4, 7.3, 7., 6.4, 7.1, 6.7, 7.6, 6.8 };
	std::vector<double> y{ 4.5, 5.4, 6.1, 6.1, 5.4, 5., 4.1, 5.5 };

	ZTest statistical_test(x, y);

	// Act
	const bool result = statistical_test.Perform();
	const auto results = statistical_test.Results();

	// Assert
	EXPECT_EQ(result, true);
	EXPECT_NEAR(results.at("z"), 6.1280815146654328, 1e-14);
	EXPECT_NEAR(results.at("pval"), 8.8945016827014375e-10, 1e-10);
	EXPECT_NEAR(results.at("x1-bar"), 7.0181818181818167, 1e-14);
	EXPECT_NEAR(results.at("sx1"), 0.46436662631627990, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("n1"), 11.0);
	EXPECT_NEAR(results.at("x2-bar"), 5.2625000000000002, 1e-14);
	EXPECT_NEAR(results.at("sx2"), 0.70698050084244091, 1e-14);
	EXPECT_DOUBLE_EQ(results.at("n2"), 8.0);
}
