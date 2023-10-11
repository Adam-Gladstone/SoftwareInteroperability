#include "pch.h"
#include "DataManager.h"
#include "DataManager.g.cpp"

#include <string>
#include <vector>

#include "Conversions.h"

namespace winrt::StatisticsLibraryWRC::implementation
{
    uint64_t DataManager::CountDataSets()
    {
        return m_dataManager.CountDataSets();
    }

    bool DataManager::Add(hstring const& name, winrt::Windows::Foundation::Collections::IVector<double> const& data)
    {
        std::vector<double> _data(data.Size(), 0.0);
        data.GetMany(0, _data);
        std::string _name = winrt::to_string(name);

        return m_dataManager.Add(_name, _data);
    }

    bool DataManager::Remove(hstring const& name)
    {
        std::string _name = winrt::to_string(name);

        return m_dataManager.Remove(_name);
    }

    winrt::Windows::Foundation::Collections::IVector<double> DataManager::GetDataSet(hstring const& name)
    {
        std::vector<double> _data = m_dataManager.GetDataSet(winrt::to_string(name));

        winrt::Windows::Foundation::Collections::IVector<double> data = winrt::single_threaded_vector<double>(std::move(_data));
        return data;
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> DataManager::ListDataSets()
    {
        winrt::Windows::Foundation::Collections::IVector<IInspectable> dataSets = winrt::single_threaded_vector<IInspectable>();

        std::vector<StatisticsLibrary::DataSetInfo> _dataSets = m_dataManager.ListDataSets();
        for (const auto& _dataSet : _dataSets)
        {
            StatisticsLibraryWRC::DataSet dataSet = winrt::make<implementation::DataSet>();

            dataSet.Name(winrt::to_hstring(_dataSet.first));
            dataSet.Size(_dataSet.second);

            dataSets.Append(winrt::box_value(dataSet));
        }
        return dataSets;
    }

    void DataManager::ClearDataSets()
    {
        m_dataManager.ClearDataSets();
    }
}
