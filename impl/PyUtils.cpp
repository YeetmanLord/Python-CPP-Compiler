#include <iostream>
#include <string>
#include "PyUtils.h"

using namespace std;

string pyUtils::pyInput(string prompt)
{
    cout << prompt;
    string val;
    getline(cin, val);
    return val;
}
