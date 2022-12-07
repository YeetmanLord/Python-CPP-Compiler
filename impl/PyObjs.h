#include <iostream>
#include <string>

using namespace std;

template <typename PrimType>
class PyObject {
    private:
        PrimType value;
        string pyType;
    public:
        PrimType getValue();
        void setValue(PrimType newValue);

        // Assignment
        PyObject &operator=(const PyObject<PrimType> &);

        // Increment
        PyObject &operator++();
        template <class PyObject>
        friend PyObject operator++(PyObject temp);
        PyObject &operator--();
        template <class PyObject>
        friend PyObject operator--(PyObject temp);

        // Addition/Subtraction
        template <class PyObject>
        friend PyObject operator+(const PyObject &, const PyObject &);
        template <class PyObject>
        friend PyObject operator-(const PyObject &, const PyObject &);
        template <class PyObject>
        friend PyObject &operator+=(PyObject &, const PyObject &);
        template <class PyObject>
        friend PyObject &operator-=(PyObject &, const PyObject &);

        // Multiplication/Division
        template <class PyObject>
        friend PyObject operator*(const PyObject &, const PyObject &);
        template <class PyObject>
        friend PyObject operator/(const PyObject &, const PyObject &);
        template <class PyObject>
        friend PyObject &operator*=(PyObject &, const PyObject &);
        template <class PyObject>
        friend PyObject &operator/=(PyObject &, const PyObject &);

        // Power
        template <class PyObject>
        friend PyObject operator^(const PyObject &, const PyObject &);
        template <class PyObject>
        friend PyObject &PyObject::operator^=(const PyObject &);

        // Comparision
        template <class PyObject>
        friend bool operator==(const PyObject &, const PyObject &);
        template <class PyObject>
        friend bool operator!=(const PyObject &, const PyObject &);
    
        template <class PyObject>
        friend bool operator>(const PyObject &, const PyObject &);
        template <class PyObject>
        friend bool operator>=(const PyObject &, const PyObject &);
        template <class PyObject>
        friend bool operator<(const PyObject &, const PyObject &);
        template <class PyObject>
        friend bool operator<=(const PyObject &, const PyObject &);

};