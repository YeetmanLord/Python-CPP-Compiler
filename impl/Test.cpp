#include <iostream>
#include <string>
#include <any>
#include "PyUtils.cpp"
#include "PyObjs.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    PyObject a = python::pyInputObject("Test: ");
    PyObject b = python::pyInputObject("Test 2: ");
    python::pyPrintF("Hello, ${pyreplace}. ${pyreplace}?", a, b);
    return 0;
}
