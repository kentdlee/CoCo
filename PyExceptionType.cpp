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

PyObject* PyExceptionType::__call__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,"TypeError: expected 1 arguments, got " + args->size());
    }
    
    return new PyException(PYEXCEPTION,(*args)[0]);
}