#ifndef _PY_OBJ

#define _PY_OBJ

#include <iostream>
#include <string>

using namespace std;

template <typename PrimType>
class PyObject
{
private:
    PrimType value;
    string pyType;

public:
    PyObject();
    PyObject(const PyObject &);
    PyObject(const PrimType &);

    PrimType getValue();
    void setValue(PrimType newValue);

    string getPyType();

    string toString();

    // Assignment
    PyObject &operator=(const PyObject<PrimType> &);

    // Increment
    PyObject &operator++();
    PyObject operator++(int temp);
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
    template <typename T>
    friend ostream &operator<<(ostream &os, const PyObject<T> &obj)
    {
        os << obj.value;
        return os;
    }
    template <typename T>
    friend istream &operator>>(istream &is, PyObject<T> &obj)
    {
        string s;
        is >> s;
        // PARSE THE TYPE FROM CONTEXT
        obj.setValue(s);

        return is;
    }
};
#endif