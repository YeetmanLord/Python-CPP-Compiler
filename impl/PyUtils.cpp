#include <iostream>
#include <string>

using namespace std;

namespace pyUtils
{
    string pyInput(string prompt) {
        cout << prompt;
        string val;
        cin >> val;
        return val;
    }
} // namespace pyUtils
