// Conversion.cpp: type conversion functions
//
#include "Conversion.h"

//
// Conversion functions
//
namespace Conversion
{
    //
    // Convert a PyObject into a vector of doubles
    //
    std::vector<double> ObjectToVector(PyObject* o)
    {
        std::size_t size = PyList_Size(o);
        std::vector<double> data;

        for (std::size_t i = 0; i < size; ++i)
        {
            double d = PyFloat_AsDouble(PyList_GetItem(o, i));
            data.emplace_back(d);
        }
        return data;
    }

    //
    // Convert a PyObject into a vector of doubles
    //
    std::vector<long> ObjectToLongVector(PyObject* o)
    {
        std::size_t size = PyList_Size(o);
        std::vector<long> data;

        for (std::size_t i = 0; i < size; ++i)
        {
            long n = PyLong_AsLong(PyList_GetItem(o, i));
            data.emplace_back(n);
        }
        return data;
    }

    //
    // Convert a PyObject into a vector of strings
    //
    std::vector<std::string> ObjectToStringVector(PyObject* o)
    {
        std::vector<std::string> strings;
        if (o != nullptr)
        {
            std::size_t size = PyList_Size(o);
            for (std::size_t i = 0; i < size; ++i)
            {
                std::string s((char*)PyUnicode_1BYTE_DATA(PyList_GetItem(o, i)));
                strings.emplace_back(s);
            }
        }
        return strings;
    }

    //
    // Convert a map into a PyObject
    //
    PyObject* MapToObject(const std::unordered_map<std::string, double>& results)
    {
        PyObject* dict = PyDict_New();

        for (const auto& result : results)
        {
            PyObject* key = PyUnicode_FromString(result.first.c_str());
            PyObject* val = PyFloat_FromDouble(result.second);

            int success = PyDict_SetItem(dict, key, val);
            Py_XDECREF(key);
            Py_XDECREF(val);
            if (success < 0)
            {
                Py_XDECREF(dict);
                return nullptr;
            }
        }
        return dict;
    }

    //
    // Convert a vector of doubles into a PyObject
    //
    PyObject* VectorToObject(const std::vector<double>& results)
    {
        const std::size_t size = results.size();
        PyObject* list = PyList_New(size);

        for(std::size_t i = 0; i < size; ++i)
        {
            double d = results[i];
            int success = PyList_SetItem(list, i, Py_BuildValue("d", d));
            if (success < 0)
            {
                Py_XDECREF(list);
                return nullptr;
            }
        }
        return list;
    }
}
