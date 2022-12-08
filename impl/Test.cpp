#include <iostream>
#include <string>
#include "PyUtils.h"
#include "PyObjs.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    PyObject<string> pyObj("123");
    cout << pyObj.getValue();
    cout << pyObj;
    return 0;
}
