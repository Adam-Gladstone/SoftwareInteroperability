// DataManager.cpp

#include "pch.h"

#include "Conversion.h"

#include "TimeSeries.h"


namespace StatsCLR
{
	//
	// Construction
	//
	TimeSeries::TimeSeries(List<System::DateTime>^ dates, List<double>^ observations)
	{
		STATS_TRY
		std::vector<StatisticsLibrary::Date> _dates = Conversion::ListToVector(dates);
		std::vector<double> _observations = Conversion::ListToVector(observations);
		m_timeSeries = new StatisticsLibrary::TimeSeries(_dates, _observations);
		STATS_CATCH
	}
	//
	// Destructor
	//
	TimeSeries::~TimeSeries()
	{
		this->!TimeSeries();
	}

	//
	// Finalizer
	//
	TimeSeries::!TimeSeries()
	{
		delete m_timeSeries;
	}

	//
	// Compute a simple moving average of size = window
	//
	List<double>^ TimeSeries::MovingAverage(int window)
	{
		STATS_TRY
		std::vector<double> results = m_timeSeries->MovingAverage(window);
		return Conversion::VectorToList(results);
		STATS_CATCH
	}
}
