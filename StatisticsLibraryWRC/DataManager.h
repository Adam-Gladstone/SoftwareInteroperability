#pragma once
#include "DataSet.h"

#include "DataSet.g.h"
#include "DataManager.g.h"


#include "..\Common\include\DataManager.h"

// https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/binding-property


namespace winrt::StatisticsLibraryWRC::implementation
{
    struct DataManager : DataManagerT<DataManager>
    {
        DataManager() = default;

        uint64_t CountDataSets();

        bool Add(hstring const& name, winrt::Windows::Foundation::Collections::IVector<double> const& data);

        bool Remove(hstring const& name);

        winrt::Windows::Foundation::Collections::IVector<double> GetDataSet(hstring const& name);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> ListDataSets();

        void ClearDataSets();

    private:
        StatisticsLibrary::DataManager m_dataManager;
    };
}
namespace winrt::StatisticsLibraryWRC::factory_implementation
{
    struct DataManager : DataManagerT<DataManager, implementation::DataManager>
    {
    };
}
