#pragma once

#include "..\..\Common\include\TimeSeries.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;

namespace StatsCLR
{
	// The TimeSeries wrapper class
	public ref class TimeSeries
	{
	public:
		// Constructor
		TimeSeries(List<System::DateTime>^ dates, List<double>^ observations);

		// Finalizer
		!TimeSeries();

		// Destruction
		~TimeSeries();

		// Compute a simple moving average of size = window
		List<double>^ MovingAverage(int window);

	private:
		// Native pointer to the underlying C++ class
		StatisticsLibrary::TimeSeries* m_timeSeries;
	};
}
