#pragma once

#include "..\..\Common\include\StatisticalTests.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;

namespace StatsCLR 
{
	public ref class TTest 
	{
	public:
		// Constructors

		// Summary data: population mean, sample mean, sample standard deviation, sample size.
		TTest(double mu0, double x_bar, double sx, double n);

		// One-sample: population mean, sample.
		TTest(double mu0, List<double>^ x1);

		// Two-sample
		TTest(List<double>^ x1, List<double>^ x2);

		// Finalizer
		!TTest();
		
		// Destructor
		~TTest();

		// Perform the test
		bool Perform();

		// Retrieve the results
		Dictionary<String^, double>^ Results();

	private:
		// Native pointer to the underlying C++ class
		StatisticsLibrary::TTest* m_test;
	};

	public ref class ZTest
	{
	public:
		// Constructors

		// Summary data: population mean, sample mean, sample standard deviation, sample size.
		ZTest(double mu0, double x_bar, double sx, double n);

		// One-sample: population mean, sample.
		ZTest(double mu0, List<double>^ x1);

		// Two-sample
		ZTest(List<double>^ x1, List<double>^ x2);

		// Finalizer
		!ZTest();

		// Destructor
		~ZTest();

		// Perform the test
		bool Perform();

		// Retrieve the results
		Dictionary<String^, double>^ Results();

	private:
		// Native pointer to the underlying C++ class
		StatisticsLibrary::ZTest* m_test;
	};
}
