#include <iostream>
#include <string>
#include "PyUtils.cpp"
#include "PyObjs.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int i = stoi(pyUtils::pyInput("Type in a number: "));
    cout << typeid(i).name() << " " << i;
    return 0;
}
