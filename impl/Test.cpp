#include <iostream>
#include <string>
#include <any>
#include "PyUtils.cpp"
#include "PyObjs.cpp"

using namespace std;
using namespace python;

int main(int argc, char const *argv[])
{
    PyString pyString = "Hello World!";
    cout << pyString << endl;
    char* stuff = new char[50];
    for (int i = 0; i < 49; ++i) {
        stuff[i] = 'a';
    }
    stuff[49] = '\0';
    delete [] stuff;
    return 0;
}
