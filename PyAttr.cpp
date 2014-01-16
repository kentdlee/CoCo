/* 
 * File:   PyAttr.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 27, 2013, 5:11 PM
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

#include "PyAttr.h"
#include "PyType.h"
#include "PyStr.h"
#include <sstream>
using namespace std;

PyAttr::PyAttr(PyObject* self, string method) : PyCallable() {
    this->self = self;
    this->method = method;
}

PyAttr::~PyAttr() {
    try {
        delete self;
    } catch (...) {}
}

PyType* PyAttr::getType() {
    return PyTypes[PyBuiltInType];
}


PyObject* PyAttr::__call__(vector<PyObject*>* args) {
    return self->callMethod(method,args);
}


string PyAttr::toString() {
    ostringstream s;
    s << "<built-in method " << method << " of " << self->getType()->toString() << " object at " << this << ">";
    return s.str();
}