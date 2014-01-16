/* 
 * File:   PyCallable.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 17, 2013, 12:21 AM
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
 */

#include "PyCallable.h"
#include "PyException.h"

PyCallable::PyCallable() : PyObject() {
    dict["__call__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyCallable::__call__);
}

PyCallable::PyCallable(const PyCallable& orig) {
}

PyCallable::~PyCallable() {
}
