// DataManager.cpp : Defines the functions for the entity.
//

#include <stdexcept>

#include "DataManager.h"

namespace StatisticsLibrary
{
	//
	// Retrieve the number of data sets currently available
	//
	auto DataManager::CountDataSets() const -> std::size_t
	{
		return m_data_sets.size();
	}

	//
	// Clear the data sets in the collection
	//
	void DataManager::ClearDataSets()
	{
		m_data_sets.clear();
	}

	//
	// Add the named data set to the collection
	//
	auto DataManager::Add(const std::string& name, const std::vector<double>& vals) -> bool
	{
		if (name.empty())
		{
			throw std::invalid_argument("A non-empty data set name is required.");
		}

		if (vals.empty())
		{
			throw std::invalid_argument("A non-empty set of values is required.");
		}

		const auto [_, inserted] = m_data_sets.insert_or_assign(name, vals);
		// The bool component is true if the insertion took place and false if the assignment took place.
		return inserted;
	}

	//
	// Remove the named data set from the collection
	//
	auto DataManager::Remove(const std::string& name) -> bool
	{
		bool result = false;
		if (!name.empty())
		{
			// Returns the number of elements removed (0 or 1).
			result = m_data_sets.erase(name) > 0;

		}
		return result;
	}

	//
	// Retrieve the named data set from the collection
	//
	auto DataManager::GetDataSet(const std::string& name) const -> std::vector<double>
	{
		if (name.empty())
		{
			throw std::invalid_argument("A non-empty data set name is required.");
		}

		const auto result = m_data_sets.find(name);
		if (result != m_data_sets.end())
		{
			return result->second;
		}
		return std::vector<double>();
	}

	//
	// Retrieve the names of the data sets in the current collection
	//
	auto DataManager::ListDataSets() const -> std::vector<DataSetInfo>
	{
		std::vector<DataSetInfo> dataSets;
		for (const auto& [key, collection] : m_data_sets)
		{ 
			dataSets.emplace_back(DataSetInfo(key, collection.size()));
		}
		return dataSets;
	}
}
