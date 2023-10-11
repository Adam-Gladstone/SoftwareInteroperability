#include "pch.h"
#include "DataSet.h"
#include "DataSet.g.cpp"

namespace winrt::StatisticsLibraryWRC::implementation
{
    hstring DataSet::Name()
    {
        return winrt::to_hstring(name);
    }
    
    void DataSet::Name(hstring const& value)
    {
        name = winrt::to_string(value);
    }
    
    uint64_t DataSet::Size()
    {
        return count;
    }
    
    void DataSet::Size(uint64_t value)
    {
        count = value;
    }
}
