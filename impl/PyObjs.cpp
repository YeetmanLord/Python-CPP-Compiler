#ifndef _PY_OBJ

#define _PY_OBJ

#include <iostream>
#include <string>
#include <any>

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

class PyObject
{
private:
    any value;
    string pyType;

public:
    PyObject()
    {
        pyType = "null";
    }

    PyObject(const PyObject &other)
    {
        value = other.value;
        pyType = other.pyType;
    }

    PyObject(const any &other)
    {
        value = other;
        pyType = getType(other);
    }

    ~PyObject()
    {
    }

    any getValue()
    {
        return value;
    }

    void setValue(any v)
    {
        value = v;
        pyType = getType(v);
    }

    string getPyType()
    {
        return pyType;
    }

    string toString()
    {
        if (value.has_value())
        {
            if (value.type() == typeid(long))
            {
                return to_string(any_cast<long>(value));
            }
            else if (value.type() == typeid(double))
            {
                return to_string(any_cast<double>(value));
            }
            else if (value.type() == typeid(bool))
            {
                bool b = any_cast<bool>(value);
                if (b)
                {
                    return "True";
                }
                else
                {
                    return "False";
                }
            }
            else if (value.type() == typeid(int))
            {
                return to_string(any_cast<int>(value));
            }
            else if (value.type() == typeid(float))
            {
                return to_string(any_cast<float>(value));
            }
            else if (value.type() == typeid(char))
            {
                return to_string(any_cast<char>(value));
            }
            return any_cast<string>(value);
        }
        return "";
    }

    // Assignment
    PyObject &operator=(const PyObject &other)
    {
        value = other.value;
        pyType = other.pyType;
        return *this;
    }

    // Increment
    PyObject &operator++()
    {
        if (pyType == "int" || pyType == "float")
        {
            if (pyType == "int")
            {
                value = (any_cast<int>(value)) + 1;
            }
            else
            {
                value = (any_cast<double>(value)) + 1.0;
            }
            return *this;
        }
        throw("Invalid Operation Exception: Cannot increment a " + pyType);
    }
    PyObject operator++(int temp)
    {
        if (pyType == "int" || pyType == "float")
        {
            PyObject aux;
            aux = *this;
            ++(*this);
            return aux;
        }
        throw("Invalid Operation Exception: Cannot increment a " + pyType);
    }
    // PyObject &operator--();
    // template <class PyObject>
    // PyObject operator--(PyObject temp);

    // Addition/Subtraction
    // template <class PyObject>
    // friend PyObject operator+(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend PyObject operator-(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend PyObject &operator+=(PyObject &, const PyObject &);
    // template <class PyObject>
    // friend PyObject &operator-=(PyObject &, const PyObject &);

    // // Multiplication/Division
    // template <class PyObject>
    // friend PyObject operator*(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend PyObject operator/(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend PyObject &operator*=(PyObject &, const PyObject &);
    // template <class PyObject>
    // friend PyObject &operator/=(PyObject &, const PyObject &);

    // // Power
    // template <class PyObject>
    // friend PyObject operator^(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend PyObject &PyObject::operator^=(const PyObject &);

    // // Comparision
    // template <class PyObject>
    // friend bool operator==(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend bool operator!=(const PyObject &, const PyObject &);

    // template <class PyObject>
    // friend bool operator>(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend bool operator>=(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend bool operator<(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend bool operator<=(const PyObject &, const PyObject &);

    // // Modulo
    // template <class PyObject>
    // friend PyObject operator%(const PyObject &, const PyObject &);
    // template <class PyObject>
    // friend PyObject &operator%=(PyObject &, const PyObject &);

    // //Square Root Function
    // template <class PyObject>
    // friend PyObject sqrt(PyObject &a);

    // Read and Write
    friend ostream &operator<<(ostream &os, PyObject &obj)
    {
        os << obj.toString();
        return os;
    }

    friend istream &operator>>(istream &is, PyObject &obj)
    {
        string s;
        is >> s;
        // PARSE THE TYPE FROM CONTEXT
        obj.setValue(s);

        return is;
    }
};
#endif