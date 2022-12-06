#include "PyObjs.h"
#include <string>

template <typename PrimType>
string getType(PrimType value) {
    switch (typeid(value)) {
        
    }
}

template <typename PrimType>
PrimType PyObject<PrimType>::getValue() {
    return value;
}

void PyObject<PrimType>::setValue(PrimType value) {
    
}