#pragma once

#define PY_SSIZE_T_CLEAN
//
// Prevent linking against pythonXY_d.lib
//
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

// https://github.com/microsoft/onnxruntime/issues/9735
#define _STL_CRT_SECURE_INVALID_PARAMETER(expr) _CRT_SECURE_INVALID_PARAMETER(expr)

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#define STATS_TRY try{

#define STATS_CATCH \
    }catch(const std::exception& e){  \
        PyErr_SetString(PyExc_RuntimeError, e.what());\
        return nullptr;\
    }


namespace Conversion
{
    // Convert a PyObject into a vector of doubles
    std::vector<double> ObjectToVector(PyObject* args);

    // Convert a PyObject into a vector of long
    std::vector<long> ObjectToLongVector(PyObject* args);

    // Convert a PyObject into a vector of strings
    std::vector<std::string> ObjectToStringVector(PyObject* o);

    // Convert a map into a PyObject
    PyObject* MapToObject(const std::unordered_map<std::string, double>& results);

    // Convert a vector of doubles into a PyObject
    PyObject* VectorToObject(const std::vector<double>& results);
}