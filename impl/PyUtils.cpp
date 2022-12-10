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
        int size = phrase.size();
        for (int x = 0; x < s.size() - size; x++)
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
        int size = phrase.size();
        vector<string> arr(lenArr);
        int last = 0;
        int index = 0;
        for (int x = 0; x < s.size() - size; x++)
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
        auto values = {args...};
        int index = 0;
        for (auto i = values.begin(); i != values.end(); ++i)
        {
            cout << &split[index];
            cout << *i;
            index++;
        }
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
            cout << any_cast<PyObject>(*i).toString();
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

} // namespace pyUtils

#endif