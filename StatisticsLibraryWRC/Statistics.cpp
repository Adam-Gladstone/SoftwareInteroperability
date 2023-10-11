#include "pch.h"
#include "Statistics.h"
#include "Statistics.g.cpp"

#include <string>
#include <vector>
#include <algorithm>

#include "Conversions.h"

#include "..\Common\include\DescriptiveStatistics.h"
#include "..\Common\include\StatisticsLibrary.h"

namespace winrt::StatisticsLibraryWRC::implementation
{
    winrt::Windows::Foundation::Collections::IMap<hstring, double> Statistics::DescriptiveStatistics(
		winrt::Windows::Foundation::Collections::IVector<double> const& data)
    {
		std::vector<double> _data( data.Size(), 0.0 );
		data.GetMany(0, _data);
		
		std::vector<std::string> _keys;
		
		const auto _results = StatisticsLibrary::GetDescriptiveStatistics(_data, _keys);

		winrt::Windows::Foundation::Collections::IMap<hstring, double> results = Conversions::ResultsToMap(_results);
		return results;
    }

	winrt::Windows::Foundation::Collections::IMap<hstring, double> Statistics::DescriptiveStatistics(
		winrt::Windows::Foundation::Collections::IVector<double> const& data,
		winrt::Windows::Foundation::Collections::IVector<hstring> const& keys)
	{
		std::vector<double> _data(data.Size(), 0.0);
		data.GetMany(0, _data);

		std::vector<std::string> _keys;
		//std::transform(keys.begin(), keys.end(), _keys.begin(), [](const hstring& s) { return winrt::to_string(s); });
		for (const auto& key : keys)
			_keys.push_back(winrt::to_string(key));

		const auto _results = StatisticsLibrary::GetDescriptiveStatistics(_data, _keys);

		winrt::Windows::Foundation::Collections::IMap<hstring, double> results = Conversions::ResultsToMap(_results);
		return results;
	}

	winrt::Windows::Foundation::Collections::IMap<hstring, double> Statistics::LinearRegression(
		winrt::Windows::Foundation::Collections::IVector<double> const& xs,
		winrt::Windows::Foundation::Collections::IVector<double> const& ys)
	{
		std::vector<double> _xs(xs.Size(), 0.0);
		xs.GetMany(0, _xs);

		std::vector<double> _ys(ys.Size(), 0.0);
		ys.GetMany(0, _ys);

		const auto _results = StatisticsLibrary::LinearRegression(_xs, _ys);

		winrt::Windows::Foundation::Collections::IMap<hstring, double> results = Conversions::ResultsToMap(_results);
		return results;
	}
}
