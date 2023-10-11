#pragma once
#include "ZTest.g.h"

#include "..\Common\include\StatisticalTests.h"


namespace winrt::StatisticsLibraryWRC::implementation
{
    struct ZTest : ZTestT<ZTest>
    {
        ZTest() = default;

        ZTest(double mu0, double x_bar, double sx, double n);

        ZTest(double mu0, winrt::Windows::Foundation::Collections::IVector<double> const& x1);

        ZTest(winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<double>> const& data);

        bool Perform();

        winrt::Windows::Foundation::Collections::IMap<hstring, double> Results();

    private:
        StatisticsLibrary::ZTest m_test;
    };
}
namespace winrt::StatisticsLibraryWRC::factory_implementation
{
    struct ZTest : ZTestT<ZTest, implementation::ZTest>
    {
    };
}
