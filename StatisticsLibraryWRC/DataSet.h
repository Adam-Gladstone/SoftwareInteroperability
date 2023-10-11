#pragma once
#include "DataSet.g.h"

namespace winrt::StatisticsLibraryWRC::implementation
{
    struct DataSet : DataSetT<DataSet>
    {
        DataSet() = default;

        hstring Name();
        void Name(hstring const& value);

        uint64_t Size();
        void Size(uint64_t value);

    private:
        std::string name{};
        std::size_t count{};
    };
}
namespace winrt::StatisticsLibraryWRC::factory_implementation
{
    struct DataSet : DataSetT<DataSet, implementation::DataSet>
    {
    };
}
