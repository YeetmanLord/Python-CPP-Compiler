#include <iostream>
#include <string>
#include <any>
#include "PyUtils.cpp"
#include "PyObjs.cpp"

using namespace std;
using namespace python;

int main(int argc, char const *argv[])
{
    unique_ptr<PyObject> pyString = make_unique<PyString>(PyString("Hello World!"));
    cout << pyString.get()->myType() << endl;
    return 0;
}
