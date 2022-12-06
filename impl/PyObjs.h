#include <string>

template <typename PrimType>
class PyObject {
    private:
        PrimType value;
        string pyType;
    public:
        friend PrimType getValue();
        friend void setValue(PrimType newValue);

        // Assignment
        friend PyObject &operator=(const PyObject &);

        // Increment
        friend PyObject &operator++();
        friend PyObject operator++(PrimType temp);
        friend PyObject &operator--();
        friend PyObject operator--(PrimType temp);

        // Addition/Subtraction
        friend PyObject operator+(const PyObject &, const PyObject &);
        friend PyObject operator-(const PyObject &, const PyObject &);
        friend PyObject &operator+=(PyObject &, const PyObject &);
        friend PyObject &operator-=(PyObject &, const PyObject &);

        // Multiplication/Division
        friend PyObject operator*(const PyObject &, const PyObject &);
        friend PyObject operator/(const PyObject &, const PyObject &);
        friend PyObject &operator*=(PyObject &, const PyObject &);
        friend PyObject &operator/=(PyObject &, const PyObject &);

        // Power
        friend PyObject operator^(const PyObject &, const PyObject &);
        friend PyObject &operator^=(const PyObject &);

        // Comparision
        friend bool operator==(const PyObject &, const PyObject &);
        friend bool operator!=(const PyObject &, const PyObject &);
    
        friend bool operator>(const PyObject &, const PyObject &);
        friend bool operator>=(const PyObject &, const PyObject &);
        friend bool operator<(const PyObject &, const PyObject &);
        friend bool operator<=(const PyObject &, const PyObject &);

};