#include "pch.h"
#include "ZTest.h"
#include "ZTest.g.cpp"

#include <string>
#include <vector>

#include "Conversions.h"

namespace winrt::StatisticsLibraryWRC::implementation
{
    ZTest::ZTest(double mu0, double x_bar, double sx, double n)
        : m_test(mu0, x_bar, sx, n)
    {
    }

    ZTest::ZTest(double mu0, winrt::Windows::Foundation::Collections::IVector<double> const& x1)
        : m_test(mu0, Conversions::ToVector(x1))
    {
    }

    ZTest::ZTest(winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<double>> const& data)
        : m_test(Conversions::ToVector(data.Lookup(L"x1")), Conversions::ToVector(data.Lookup(L"x2")))
    {
    }

    bool ZTest::Perform()
    {
        return m_test.Perform();
    }

    winrt::Windows::Foundation::Collections::IMap<hstring, double> ZTest::Results()
    {
        const auto _results = m_test.Results();
        winrt::Windows::Foundation::Collections::IMap<hstring, double> results = Conversions::ResultsToMap(_results);
        return results;
    }
}
