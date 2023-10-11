#include "pch.h"
#include "Conversions.h"

namespace Conversions
{
    std::vector<double> ToVector(winrt::Windows::Foundation::Collections::IVector<double> const& data)
    {
        std::vector<double> _data(data.Size(), 0.0);
        data.GetMany(0, _data);
        return _data;
    }

    winrt::Windows::Foundation::Collections::IMap<winrt::hstring, double> ResultsToMap(const std::unordered_map<std::string, double>& input)
    {
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, double> output = winrt::single_threaded_map<winrt::hstring, double>();
        for (const auto& [key, value] : input)
        {
            output.Insert(winrt::to_hstring(key), value);
        }
        return output;
    }
}
