#include <iostream>
#include <string>
#include <vector>
#include "PyObjs.h"

using namespace std;

namespace python
{
    string pyInput(string);
    int stringCount(const string, string);
    vector<string> stringSplit(const string, string);
    template <class PyObject, class... TArgs>
    void pyPrintF(PyObject, TArgs... args);
    template <class PyObject>
    void pyPrint(PyObject);
    PyObject<string> pyInputObject(string);

} // namespace pyUtils