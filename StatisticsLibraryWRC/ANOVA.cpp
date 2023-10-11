#include "pch.h"
#include "ANOVA.h"
#include "ANOVA.g.cpp"

#include <string>
#include <vector>

#include "Conversions.h"

namespace winrt::StatisticsLibraryWRC::implementation
{
    ANOVA::ANOVA(
        winrt::Windows::Foundation::Collections::IVector<double> const& x1, 
        winrt::Windows::Foundation::Collections::IVector<double> const& x2, 
        winrt::Windows::Foundation::Collections::IVector<double> const& x3
    )
        : m_test(
            Conversions::ToVector(x1), 
            Conversions::ToVector(x2), 
            Conversions::ToVector(x3)
        )
    {
    }

    bool ANOVA::Perform()
    {
        return m_test.Perform();
    }

    winrt::Windows::Foundation::Collections::IMap<hstring, double> ANOVA::Results()
    {
        const auto _results = m_test.Results();
        winrt::Windows::Foundation::Collections::IMap<hstring, double> results = Conversions::ResultsToMap(_results);
        return results;
    }
}
