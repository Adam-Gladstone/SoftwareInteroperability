#include "pch.h"
#include "FTest.h"
#include "FTest.g.cpp"

#include <string>
#include <vector>

#include "Conversions.h"

namespace winrt::StatisticsLibraryWRC::implementation
{
    FTest::FTest(double sx1, double sx2, double n1, double n2)
        : m_test(sx1, sx2, n1, n2)
    {
    }

    FTest::FTest(winrt::Windows::Foundation::Collections::IVector<double> const& x1, winrt::Windows::Foundation::Collections::IVector<double> const& x2)
        : m_test(Conversions::ToVector(x1), Conversions::ToVector(x2))
    {
    }

    bool FTest::Perform()
    {
        return m_test.Perform();
    }

    winrt::Windows::Foundation::Collections::IMap<hstring, double> FTest::Results()
    {
        const auto _results = m_test.Results();
        winrt::Windows::Foundation::Collections::IMap<hstring, double> results = Conversions::ResultsToMap(_results);
        return results;
    }
}
