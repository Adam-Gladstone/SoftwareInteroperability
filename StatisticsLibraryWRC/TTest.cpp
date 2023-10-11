#include "pch.h"
#include "TTest.h"
#include "TTest.g.cpp"

#include <string>
#include <vector>

#include "Conversions.h"

namespace winrt::StatisticsLibraryWRC::implementation
{
    TTest::TTest(double mu0, double x_bar, double sx, double n)
        : m_test(mu0, x_bar, sx, n)
    {
    }

    TTest::TTest(double mu0, winrt::Windows::Foundation::Collections::IVector<double> const& x1)
        : m_test(mu0, Conversions::ToVector(x1))
    {
    }

    TTest::TTest(winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<double>> const& data)
        : m_test(Conversions::ToVector(data.Lookup(L"x1")), Conversions::ToVector(data.Lookup(L"x2")))
    {
    }

    bool TTest::Perform()
    {
        return m_test.Perform();
    }

    winrt::Windows::Foundation::Collections::IMap<hstring, double> TTest::Results()
    {
        const auto _results = m_test.Results();
        winrt::Windows::Foundation::Collections::IMap<hstring, double> results = Conversions::ResultsToMap(_results);
        return results;
    }
}
