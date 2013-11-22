/* 
 * File:   PyExceptionType.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on April 6, 2013, 10:24 PM
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

#include "PyExceptionType.h"
#include "PyException.h"
#include "PyType.h"
#include "PyStr.h"
#include "PyInt.h"

PyExceptionType::PyExceptionType(string typeString, PyTypeId id): PyType(typeString, id) {
}

PyExceptionType::~PyExceptionType() {
}

// This method may not need to override the PyType method because it also 
// return true for count == 1. However, PyType also at one time returned
// true for count == 3. Can't figure out why that was needed. May have been
// left over from a previous revision. Anyway, we'll leave this method here.
// Either way, it would have to be virtual otherwise. 
bool PyExceptionType::allowableArgCount(int count) {
    return count == 1;
}

PyObject* PyExceptionType::__call__(vector<PyObject*>* args) {
    return new PyException(PYEXCEPTION,(*args)[0]);
}