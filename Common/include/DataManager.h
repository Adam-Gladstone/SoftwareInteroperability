#pragma once

#ifdef DYNAMIC
#   ifdef STATSDLL_EXPORTS
#       define STATSDLL_API __declspec(dllexport)
#   else
#       define STATSDLL_API __declspec(dllimport)
#   endif
#else
#   define STATSDLL_API
#endif


#ifdef _MSC_VER
	#pragma warning( disable: 4251 ) // warning C4251: 'stl': class '...' needs to have dll-interface to be used by clients of class '...'
#endif

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

namespace StatisticsLibrary
{
	// Type for reporting name and size of the data set
	using DataSetInfo = std::pair<std::string, std::size_t>;

	//
	// Class to manage a collection of named data sets
	//
	class STATSDLL_API DataManager final
	{
	public:
		// Retrieve the number of data sets currently available
		[[nodiscard]]
		auto CountDataSets() const->std::size_t;

		// Add the named data set to the collection
		auto Add(const std::string& name, const std::vector<double>& vals) -> bool;

		// Remove the named data set from the collection
		auto Remove(const std::string& name) -> bool;

		// Retrieve the named data set from the collection
		[[nodiscard]]
		auto GetDataSet(const std::string& name) const->std::vector<double>;

		// Retrieve the names of the data sets in the current collection
		[[nodiscard]]
		auto ListDataSets() const->std::vector<DataSetInfo>;

		// Clear the data sets in the collection
		void ClearDataSets();

	private:
		// Collection of named data sets
		std::unordered_map<std::string, std::vector<double>> m_data_sets;
	};
}
