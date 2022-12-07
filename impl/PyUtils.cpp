#include <iostream>
#include <string>
#include "PyUtils.h"

using namespace std;

string pyUtils::pyInput(string prompt)
{
    cout << prompt;
    string val;
    cin >> val;
    return val;
}
