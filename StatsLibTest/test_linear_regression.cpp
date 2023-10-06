#include "pch.h"

#include "StatisticsLibrary.h"

using namespace StatisticsLibrary;

TEST(LinearRegressionTests, TestLinearRegression)
{
	// Arrange
	const double b0{ 1.2363636363636363 };
	const double b1{ 1.1696969696969697 };
	const double r{  0.9759805523748860 };
	const double r2{ 0.9525380386139880 };

	std::vector<double> x{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::vector<double> y{ 1, 3, 2, 5, 7, 8, 8, 9, 10, 12 };

	// Act
	const auto results = LinearRegression(x, y);

	// Assert
	EXPECT_EQ(results.at("b0"), b0);
	EXPECT_EQ(results.at("b1"), b1);
	EXPECT_NEAR(results.at("r"), r, 1e-14);
	EXPECT_NEAR(results.at("r2"), r2, 1e-14);
}

TEST(LinearRegressionTests, TestLinearRegressionNoData)
{
	// Arrange
	std::vector<double> x{ };
	std::vector<double> y{ };

	// Act / Assert
	EXPECT_THROW([[maybe_unused]] const auto results = LinearRegression(x, y), std::invalid_argument);
}

