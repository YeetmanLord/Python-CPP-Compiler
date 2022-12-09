#include <iostream>
#include <string>
#include "PyUtils.h"
#include "PyObjs.h"

using namespace std;
using namespace python;

int main(int argc, char const *argv[])
{
    PyObject<string> a = pyInputObject("Test: ");
    PyObject<string> b = pyInputObject("Test 2: ");
    pyPrintF("Hello, ${pyreplace}! ${pyreplace}?", a, b);
    return 0;
}
