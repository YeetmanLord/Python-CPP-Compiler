#include <iostream>
#include <string>
#include "PyUtils.h"
#include "PyObjs.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    PyObject<string> a = pyInputObject("Test: ");
    cout << a;
    return 0;
}
