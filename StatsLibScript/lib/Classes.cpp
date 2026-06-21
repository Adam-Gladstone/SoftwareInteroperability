// StatisticalTests.cpp: defines the functions and class that we wrap

#include "Classes.h"


namespace API
{
    namespace Data
    {
        //
        // Retrieve the number of data sets currently available
        //
        std::size_t DataManager::CountDataSets() const
        {
            return m_manager.CountDataSets();
        }

        //
        // Add the named data set to the collection
        //
        bool DataManager::Add(const std::string& name, const std::vector<double>& vals)
        {
            return m_manager.Add(name, vals);
        }

        //
        // Retrieve the named data set from the collection
        //
        std::vector<double> DataManager::GetDataSet(const std::string& name) const
        {
            return m_manager.GetDataSet(name);
        }

        //
        // Retrieve the names of the data sets in the current collection
        //
        std::vector<std::string> DataManager::ListDataSets() const
        {
            std::vector<StatisticsLibrary::DataSetInfo> datasets = m_manager.ListDataSets();
            std::vector<std::string> results;

            for (std::size_t i = 0; i < datasets.size(); ++i)
            {
                // Dataset name and count of elements
                const auto& dataset = datasets.at(i);
                //std::string info{ dataset.first + ": " + std::to_string(dataset.second) };
                std::string info{ dataset.first };

                results.emplace_back(info);
            }
            return results;
        }

        //
        // Clear the data sets in the collection
        //
        void DataManager::ClearDataSets()
        {
            m_manager.ClearDataSets();
        }
    }
}
