/* 
 * File:   PyBuiltInConcat.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on April 25, 2013, 11:27 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyBuiltInConcat.h"
#include "PyObject.h"
#include "PyException.h"
#include "PyInt.h"

#include <vector>
using namespace std;

PyBuiltInConcat::PyBuiltInConcat() : PyCallable() {
}

PyBuiltInConcat::PyBuiltInConcat(const PyBuiltInConcat& orig) {
}

PyBuiltInConcat::~PyBuiltInConcat() {
}

PyType* PyBuiltInConcat::getType() {
    return PyTypes[PyBuiltInType];
}

PyObject* PyBuiltInConcat::__call__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,"TypeError: expected 1 arguments, got " + args->size());
    }
    
    PyObject* x;

    x = (*args)[0];
    
    vector<PyObject*>* callArgs = new vector<PyObject*>();
    
    return x->callMethod("concat",callArgs);
}

string PyBuiltInConcat::callName() {
    return "concat";
}

string PyBuiltInConcat::toString() {
    return callName();
}