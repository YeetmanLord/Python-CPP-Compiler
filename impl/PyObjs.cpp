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
PyObject<PrimType> &PyObject<PrimType>::operator=(const PyObject<PrimType> &other)
{
    value = other.value;
    pyType = other.pyType;
    return *this;
}

template <typename PrimType>
PyObject<PrimType> &PyObject<PrimType>::operator++()
{
    ++value;
    return *this;
}

template <typename PrimType>
ostream &operator<<(ostream &os, PyObject<PrimType> &obj)
{
    os << obj.getValue();
    return os;
}

template <typename PrimType>
istream &operator>>(istream &is, PyObject<PrimType> &obj)
{
    string s;
    is >> s;
    // PARSE THE TYPE FROM CONTEXT
    obj.setValue(s);

    return is;
}

static PyObject<string> pyInputObject(string prompt) {
    cout << prompt;
    string val;
    getline(cin, val);
    const string cval = val;
    return PyObject<string>(cval);
}