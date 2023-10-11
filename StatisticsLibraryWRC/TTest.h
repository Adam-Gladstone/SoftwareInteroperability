#pragma once
#include "TTest.g.h"

#include "..\Common\include\StatisticalTests.h"


namespace winrt::StatisticsLibraryWRC::implementation
{
    struct TTest : TTestT<TTest>
    {
        TTest() = default;

        TTest(double mu0, double x_bar, double sx, double n);

        TTest(double mu0, winrt::Windows::Foundation::Collections::IVector<double> const& x1);

        TTest(winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<double>> const& data);

        bool Perform();

        winrt::Windows::Foundation::Collections::IMap<hstring, double> Results();

    private:
        StatisticsLibrary::TTest m_test;
    };
}
namespace winrt::StatisticsLibraryWRC::factory_implementation
{
    struct TTest : TTestT<TTest, implementation::TTest>
    {
    };
}
