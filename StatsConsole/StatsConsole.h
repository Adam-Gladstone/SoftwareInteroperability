#pragma once

#include <string>

namespace StatsConsole
{
	// Input data via the console
	bool OnEnterData(const std::string& prompt);

	// Get data from a file
	bool OnReadFile(const std::string& prompt);

	// List the data sets
	bool OnListDataSets(const std::string& prompt);

	// Display the data
	bool OnDisplayData(const std::string& prompt);

	// Retrieve the descriptive statistics for the data set
	bool OnDescriptiveStats(const std::string& prompt);

	// Perform Linear regression
	bool OnLinearRegression(const std::string& prompt);

	// Perform one-sample t-test
	bool OnOneSampleTtest(const std::string& prompt);

	// Perform two-sample t-test
	bool OnTwoSampleTtest(const std::string& prompt);

	// Close the console application
	bool OnClose(const std::string& prompt);
}