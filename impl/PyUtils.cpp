#ifndef _PY_UTILS

#define _PY_UTILS

#include <iostream>
#include <string>
#include <vector>
#include <any>
#include "PyObjs.cpp"

using namespace std;

namespace python
{
    string pyInput(string prompt)
    {
        cout << prompt;
        string val;
        getline(cin, val);
        return val;
    }
    int stringCount(const string s, string phrase)
    {
        int count = 0;
        size_t size = phrase.size();
        for (int x = 0; x < s.size() - size + 1; x++)
        {
            string sub = s.substr(x, size);
            if (sub == phrase)
            {
                count++;
            }
        }
        return count;
    }
    vector<string> stringSplit(const string s, string phrase)
    {
        const int lenArr = stringCount(s, phrase) + 1;
        size_t size = phrase.size();
        vector<string> arr(lenArr);
        size_t last = 0;
        size_t index = 0;
        for (size_t x = 0; x < s.size() - size + 1; x++)
        {
            string sub = s.substr(x, size);
            if (sub == phrase)
            {
                arr[index] = s.substr(last, x - last);
                index++;
                x += size;
                last = x;
            }
        }
        arr[index] = s.substr(last, -1);
        return arr;
    }

    template <typename... TArgs>
    void pyPrintF(PyObject pStatement, TArgs... args)
    {
        string s = pStatement.toString();
        vector<string> split = stringSplit(s, "${pyreplace}");
        vector<any> values = {args...};
        int index = 0;
        for (auto i = values.begin(); i != values.end(); ++i)
        {
            cout << *&split[index];
            unique_ptr<PyObject> ptr = make_unique(*i);
            cout << ptr.get()->toString;
            index++;
        }
        cout << *&split[index];
        cout << endl;
    }

    template <typename... TArgs>
    void pyPrintF(string pStatement, TArgs... args)
    {
        vector<string> split = stringSplit(pStatement, "${pyreplace}");
        vector<any> values = {args...};
        int index = 0;
        for (auto i = values.begin(); i != values.end(); ++i)
        {
            cout << *&split[index];
            unique_ptr<PyObject> ptr = 
            cout << i->toString();
            index++;
        }
        cout << *&split[index];
        cout << endl;
    }
    void pyPrint(PyObject pStatement)
    {
        cout << pStatement << endl;
    }

    void pyPrint(string pStatement)
    {
        cout << pStatement << endl;
    }
    PyObject pyInputObject(string prompt)
    {
        cout << prompt;
        string val;
        getline(cin, val);
        PyObject obj;
        obj.setValue(val);
        return obj;
    }

    bool isInt(const string s) {
        for (int i = 0; i < s.length(); ++i) {
            char c = s.at(i);
            if (i == 0 && c == '-') {
                continue;
            } else if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    bool pyIsDigit(const string s) {
        for (int i = 0; i < s.length(); ++i) {
            char c = s.at(i);
             if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }

} // namespace pyUtils

#endif