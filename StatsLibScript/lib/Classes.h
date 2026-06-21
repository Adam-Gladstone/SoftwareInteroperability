#pragma once

#include "../../Common/include/DataManager.h"
#include "../../Common/include/StatisticalTests.h"


#include "Conversion.h"

namespace API
{
    namespace Data
    {
        // DataManager wrapper class
        class DataManager final
        {
        public:
            // Destructor
            ~DataManager() = default;

            // Constructor
            DataManager() = default;

            // Copy constructor
            DataManager(const DataManager& other) = default;

            // Copy assignment
            DataManager& operator=(const DataManager& other) = default;

            // Retrieve the number of data sets currently available
            std::size_t CountDataSets() const;

            // Add the named data set to the collection
            bool Add(const std::string& name, const std::vector<double>& vals);

            // Retrieve the named data set from the collection
            std::vector<double> GetDataSet(const std::string& name) const;

            // Retrieve the names of the data sets in the current collection
            std::vector<std::string> ListDataSets() const;

            // Clear the data sets in the collection
            void ClearDataSets();

        private:
            StatisticsLibrary::DataManager m_manager;
        };
    }

	namespace StatisticalTests
	{
        ///////////////////////////////////////////////////////////////////////
        // TTest wrapper class
        class TTest final
        {
        public:
            ~TTest() = default;

            TTest(double mu0, double mean, double sd, double n)
                : _test(mu0, mean, sd, n)
            {
            }

            TTest(const std::string& type, double mu0, const std::vector<double>& x1)
                : _test(mu0, x1)
            {
            }

            TTest(const std::vector<double>& x1, const std::vector<double>& x2)
                : _test(x1, x2)
            {
            }

            bool Perform()
            {
                return _test.Perform();
            }

            std::map<std::string, double> Results() const
            {
                return Conversion::to_map(_test.Results());
            }

        private:
            StatisticsLibrary::TTest _test;
        };

        ///////////////////////////////////////////////////////////////////////
        // ZTest wrapper class
        class ZTest final
        {
        public:
            ~ZTest() = default;

            ZTest(double mu0, double mean, double sd, double n)
                : _test(mu0, mean, sd, n)
            {
            }

            ZTest(const std::string& type, double mu0, const std::vector<double>& x1)
                : _test(mu0, x1)
            {
            }

            ZTest(const std::vector<double>& x1, const std::vector<double>& x2)
                : _test(x1, x2)
            {
            }

            bool Perform()
            {
                return _test.Perform();
            }

            std::map<std::string, double> Results() const
            {
                return Conversion::to_map(_test.Results());
            }

        private:
            StatisticsLibrary::ZTest _test;
        };
	}
}
