#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Conversions
{
    std::vector<double> ToVector(winrt::Windows::Foundation::Collections::IVector<double> const& data);

    winrt::Windows::Foundation::Collections::IMap<winrt::hstring, double> 
        ResultsToMap(const std::unordered_map<std::string, double>& input);
}

