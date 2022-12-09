#include <iostream>
#include <string>
#include <vector>
#include "PyUtils.h"
#include "PyObjs.cpp"

using namespace std;

string python::pyInput(string prompt)
{
    cout << prompt;
    string val;
    getline(cin, val);
    return val;
}

int python::stringCount(const string s, string phrase) {
    int count = 0;
    int size = phrase.size();
    for (int x = 0; x < s.size() - size; x++) {
        string sub = s.substr(x, size);
        if (sub == phrase) {
            count++;
        }
    }
    return count;
}

vector<string> python::stringSplit(const string s, string phrase) {
    const int lenArr = stringCount(s, phrase) + 1;
    int size = phrase.size();
    vector<string> arr(lenArr);
    int last = 0;
    int index = 0;
    for (int x = 0; x < s.size() - size; x++) {
        string sub = s.substr(x, size);
        if (sub == phrase) {
            arr[index] = s.substr(last, x - last);
            index++;
            x += size;
            last = x;
        }
    }
    arr[index] = s.substr(last, -1);
    return arr;
}

PyObject<string> python::pyInputObject(string prompt) {
    cout << prompt;
    string val;
    getline(cin, val);
    return PyObject<string>(val);
}

template <class PyObject>
void python::pyPrint(PyObject pStatement) {
    cout << pStatement << endl;
}

template <class PyObject, class... TArgs>
void python::pyPrintF(PyObject pStatement, TArgs... args) {
    string s = pStatement.getValue();
    vector<string> split = stringSplit(s, "${pyreplace}");
    auto values = {args...};
    int index = 0;
    for (auto i = split.begin(); i != split.end(); ++i) {
        cout << *i;
        cout << *values[index];
        index++;
    }
    cout << endl;
}