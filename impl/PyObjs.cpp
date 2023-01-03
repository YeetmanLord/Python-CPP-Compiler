#ifndef _PY_OBJ

#define _PY_OBJ

#include <iostream>
#include <string>
#include <any>
#include <cmath>

using namespace std;

namespace python
{
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
    protected:
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

        string toString() const
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

        /* Tests if another PyObject is contained within this one */
        bool in(PyObject &other)
        {
            return false;
        }

        string myType() {
            return "Obj";
        }
    };

    class PyString : public PyObject
    {
        public: 
            PyString() {
                value = "";
                pyType = "str";
            }

            string myType() {
                return "String";
            }

            PyString(PyObject &other)
            {
                try
                {
                    value = any_cast<string>(other.getValue());
                }
                catch (bad_any_cast exception)
                {
                    cout << exception.what() << endl;
                }
            }

            PyString(string &s)
            {
                value = &s;
            }

            PyString(const char *str) {
                string s = str;
                value = s;
                pyType = "str";
            }

            PyString &operator=(string &str)
            {
                value = str;
                pyType = "str";
                return *this;
            }

            string toString()
            {
                return any_cast<string>(value);
            }

            friend PyString operator+(const PyString &obj1, const PyObject &obj2) {
                string s = any_cast<string>(obj1.value) + obj2.toString();
                return s;
            }

            friend PyString &operator+=(PyString &self, string s) {
                self.value = any_cast<string>(self.value) + s;
                return self;
            }

            friend PyString operator+(const PyString &obj1, const string &s) {
                string newValue = any_cast<string>(obj1) + s;
                return newValue;
            }

            friend PyString operator+(const string &s, const PyString &obj1) {
                string newValue = s + any_cast<string>(obj1.value);
                return newValue;
            }

            friend PyString operator+(const PyObject &obj1, const PyString &obj2) {
                string newValue = obj1.toString() + any_cast<string>(obj2.value);
                return newValue;
            }

            friend PyString operator*(const PyString &obj, const int number) {
                string newValue;
                for (int i = 0; i < number; ++i) {
                    newValue += any_cast<string>(obj.value);
                }
                return newValue;
            }

            friend ostream& operator<<(ostream& os, PyString& obj)
            {
                os << any_cast<string>(obj);
                return os;
            }
        
    };
}
#endif