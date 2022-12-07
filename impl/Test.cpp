#include <iostream>
#include <string>
#include "PyUtils.h"
#include "PyObjs.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    PyObject<int> pyObj(123);
    cout << pyObj.getValue();
    return 0;
}
