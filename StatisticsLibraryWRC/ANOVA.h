#pragma once
#include "ANOVA.g.h"

#include "..\Common\include\StatisticalTests.h"


namespace winrt::StatisticsLibraryWRC::implementation
{
    struct ANOVA : ANOVAT<ANOVA>
    {
        ANOVA() = default;

        ANOVA(winrt::Windows::Foundation::Collections::IVector<double> const& x1, winrt::Windows::Foundation::Collections::IVector<double> const& x2, winrt::Windows::Foundation::Collections::IVector<double> const& x3);

        bool Perform();

        winrt::Windows::Foundation::Collections::IMap<hstring, double> Results();

    private:
        StatisticsLibrary::ANOVA m_test;
    };
}
namespace winrt::StatisticsLibraryWRC::factory_implementation
{
    struct ANOVA : ANOVAT<ANOVA, implementation::ANOVA>
    {
    };
}
