// Conversion.cpp: defines the conversion layer

#include "Conversion.h"


namespace Conversion
{
    std::map<std::string, double> to_map(const std::unordered_map<std::string, double>& _results)
    {
        std::map<std::string, double> result_map;

        for (const auto& result : _results)
        {
            result_map[result.first] = result.second;
        }

        return result_map;
    }

}

