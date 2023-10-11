#pragma once
#include "Statistics.g.h"

namespace winrt::StatisticsLibraryWRC::implementation
{
    struct Statistics : StatisticsT<Statistics>
    {
        Statistics() = default;

        winrt::Windows::Foundation::Collections::IMap<hstring, double> DescriptiveStatistics(
            winrt::Windows::Foundation::Collections::IVector<double> const& data);

        winrt::Windows::Foundation::Collections::IMap<hstring, double> DescriptiveStatistics(
            winrt::Windows::Foundation::Collections::IVector<double> const& data,
            winrt::Windows::Foundation::Collections::IVector<hstring> const& keys);

        winrt::Windows::Foundation::Collections::IMap<hstring, double> LinearRegression(
            winrt::Windows::Foundation::Collections::IVector<double> const& xs,
            winrt::Windows::Foundation::Collections::IVector<double> const& ys);

    };
}
namespace winrt::StatisticsLibraryWRC::factory_implementation
{
    struct Statistics : StatisticsT<Statistics, implementation::Statistics>
    {
    };
}
