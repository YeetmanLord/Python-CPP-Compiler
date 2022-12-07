#include <iostream>
#include <string>
#include "PyObjs.h"

using namespace std;

template <typename PrimType>
string getType(PrimType value) {
    switch (typeid(value)) {
        
    }

    return "";
}

template <typename PrimType>
PrimType PyObject<PrimType>::getValue() {
    return value;
}

template <typename PrimType>
void PyObject<PrimType>::setValue(PrimType value) {
    
}