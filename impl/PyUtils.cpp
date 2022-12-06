#include <iostream>
#include <string>

using namespace std;

string pyInput(string prompt) {
    cout << prompt;
    string val;
    cin >> val;
    return val;
}