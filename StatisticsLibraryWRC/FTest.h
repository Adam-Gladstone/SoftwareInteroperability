#pragma once
#include "FTest.g.h"

#include "..\Common\include\StatisticalTests.h"


namespace winrt::StatisticsLibraryWRC::implementation
{
    struct FTest : FTestT<FTest>
    {
        FTest() = default;

        FTest(double sx1, double sx2, double n1, double n2);

        FTest(winrt::Windows::Foundation::Collections::IVector<double> const& x1, winrt::Windows::Foundation::Collections::IVector<double> const& x2);

        bool Perform();

        winrt::Windows::Foundation::Collections::IMap<hstring, double> Results();

    private:
        StatisticsLibrary::FTest m_test;
    };
}
namespace winrt::StatisticsLibraryWRC::factory_implementation
{
    struct FTest : FTestT<FTest, implementation::FTest>
    {
    };
}
