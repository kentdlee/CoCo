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
#include <sstream>

using namespace std;

PyExceptionType::PyExceptionType(string typeString, PyTypeId id) : PyType(typeString, id) {
}

PyExceptionType::~PyExceptionType() {
}

PyObject* PyExceptionType::__call__(vector<PyObject*>* args) {
    ostringstream msg;
    int exctype;

    if (args->size() > 2) {
        msg << "TypeError: expected 1 or 2 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION, msg.str());
    }

    if (args->size() == 1)
        return new PyException(PYEXCEPTION, (*args)[0]);

    if ((*args)[0]->getType()->typeId() != PyIntType)
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "TypeError: expected int for first argument to Exception.");
    
    exctype = ((PyInt*) (*args)[0])->getVal();
    return new PyException(exctype, (*args)[1]);
}