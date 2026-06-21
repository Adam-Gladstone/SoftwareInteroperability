#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <iostream>

#include <emscripten/bind.h>
#include <emscripten/val.h>


namespace Conversion
{
    // Convert an unordered_map into a map; emscripten doesn't have a type we can register for this
    std::map<std::string, double> to_map(const std::unordered_map<std::string, double>& _results);

    //https://github.com/emscripten-core/emscripten/issues/11070

    /**
     * Determines whether an JS value is a specified type.
     */
    inline bool is_type(emscripten::val value, const std::string &type)
    {
        return value.typeOf().as<std::string>() == type;
    }

    inline bool is_vector(emscripten::val value)
    {
        return is_type(value["size"], "function");
    }

    /**
     * Converts an input array to a vector.
     */
    template <typename T>
    std::vector<T> to_vector(emscripten::val v) 
    {
        std::vector<T> rv;

        if (v.isArray()) {
            rv = emscripten::vecFromJSArray<T>(v);
        } else if (is_vector(v)) {
            rv = v.as<std::vector<T>>();
        } else {
            // Allow single values as well
            rv = {v.as<T>()};
        }

        return rv;
    }

    /**
     * Prints vector to std out
     */
    template <typename T>
    void print(const std::string& message, const std::vector<T>& values)
    {
        std::cout << message << '\n';

        for(T value : values)
        {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}
