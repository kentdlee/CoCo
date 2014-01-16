/* 
 * File:   PyBuiltInInput.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 16, 2013, 8:26 PM
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

#include "PyBuiltInInput.h"
#include "PyException.h"
#include "PyStr.h"
#include <iostream>
#include <sstream>
using namespace std;

PyBuiltInInput::PyBuiltInInput() : PyCallable() {
}

PyBuiltInInput::PyBuiltInInput(const PyBuiltInInput& orig) {
}

PyBuiltInInput::~PyBuiltInInput() {
}

PyType* PyBuiltInInput::getType() {
    return PyTypes[PyBuiltInType];
}

PyObject* PyBuiltInInput::__call__(vector<PyObject*>* args) {
    PyObject* x;
    PyStr* y;
    string input;
    char buffer[256];
    ostringstream msg;

    if (args->size() != 1) {
         msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());
    }
    
    x = (*args)[0];

    if (x->getType()->typeId() != PyStrType) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid argument to input(): Expected str, found " + x->getType()->toString());
    }

    y = (PyStr*) x;

    cout << y->toString();

    ostringstream s;

    cin.getline(buffer, 256);
    
    while (cin.gcount() == 255) {
        s << buffer;
        cin.getline(buffer, 256);
    }
    
    s << buffer;

    return new PyStr(s.str());
}

string PyBuiltInInput::toString() {
    return "input";
}