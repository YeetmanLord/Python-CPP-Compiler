#include <iostream>
#include <string>
#include "PyObjs.h"

using namespace std;

template <typename PrimType>
static string getType(PrimType &value)
{
    if (typeid(value) == typeid(string))
    {
        return "str";
    }
    else if (typeid(value) == typeid(int))
    {
        return "int";
    }
    else if (typeid(value) == typeid(float))
    {
        return "float";
    }
    else if (typeid(value) == typeid(double))
    {
        return "float";
    }
    else if (typeid(value) == typeid(char))
    {
        return "str";
    }
    else if (typeid(value) == typeid(bool))
    {
        return "bool";
    }
    else if (typeid(value) == typeid(long))
    {
        return "int";
    }

    return "";
}

template <typename PrimType>
PyObject<PrimType>::PyObject()
{
    pyType = "null";
}

template <typename PrimType>
PyObject<PrimType>::PyObject(const PyObject &other)
{
    value = other.value;
    pyType = other.pyType;
}

template <typename PrimType>
PyObject<PrimType>::PyObject(const PrimType &other)
{
    value = other;
    pyType = getType(other);
}

template <typename PrimType>
PrimType PyObject<PrimType>::getValue()
{
    return value;
}

template <typename PrimType>
void PyObject<PrimType>::setValue(PrimType v)
{
    value = v;
    pyType = getType(v);
}

template <typename PrimType>
string PyObject<PrimType>::getPyType()
{
    return pyType;
}

template <typename PrimType>
string PyObject<PrimType>::toString() {
    return to_string(value);
}

template <typename PrimType>
PyObject<PrimType> &PyObject<PrimType>::operator=(const PyObject<PrimType> &other)
{
    value = other.value;
    pyType = other.pyType;
    return *this;
}

template <typename PrimType>
PyObject<PrimType> &PyObject<PrimType>::operator++()
{
    if (pyType == "int" || pyType == "float")
    {
        ++value;
        return *this;
    }
    throw("Invalid Operation Exception: Cannot increment a " + pyType);
}

template <typename PrimType>
PyObject<PrimType> PyObject<PrimType>::operator++(int temp)
{
    if (pyType == "int" || pyType == "float")
    {
        PyObject<PrimType> aux;
        aux = *this;
        ++(*this);
        return aux;
    }
    throw("Invalid Operation Exception: Cannot increment a " + pyType);
}
