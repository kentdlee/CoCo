/* 
 * File:   PyBuiltInLen.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 28, 2013, 10:57 AM
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

#include "PyBuiltInLen.h"
#include "PyObject.h"
#include "PyException.h"
#include "PyInt.h"

#include <vector>
#include <sstream>
using namespace std;

PyBuiltInLen::PyBuiltInLen() : PyCallable() {
}

PyBuiltInLen::PyBuiltInLen(const PyBuiltInLen& orig) {
}

PyBuiltInLen::~PyBuiltInLen() {
}

PyType* PyBuiltInLen::getType() {
    return PyTypes[PyBuiltInType];
}

PyObject* PyBuiltInLen::__call__(vector<PyObject*>* args) {
    PyObject* x;
    ostringstream msg;
    
    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }

    x = (*args)[0];
    
    vector<PyObject*>* callArgs = new vector<PyObject*>();
    
    return x->callMethod("__len__",callArgs);
}

string PyBuiltInLen::toString() {
    return "len";
}