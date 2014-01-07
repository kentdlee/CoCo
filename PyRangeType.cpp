/* 
 * File:   PyRangeType.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 23, 2013, 10:50 PM
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

#include "PyRangeType.h"
#include "PyType.h"
#include "PyException.h"
#include "PyInt.h"
#include "PyRange.h"

PyRangeType::PyRangeType(string typeString, PyTypeId id) : PyType(typeString, id) {
}

PyRangeType::~PyRangeType() {
}

PyObject* PyRangeType::__call__(vector<PyObject*>* args) {
    //cerr << "In range() with " << args->size() << " args to given to range." <<  endl;
     
    int start;
    int stop;
    int increment;
    
    switch (args->size()) {
        case 1:
            if ((*args)[0]->getType()->typeId() != PyIntType) {
                throw new PyException(PYILLEGALOPERATIONEXCEPTION,"range arguments must be of int type.");
            }
            
            start = 0;
            stop = ((PyInt*) ((*args)[0]))->getVal();
            increment = 1;
            break;
        case 2:
            if ((*args)[0]->getType()->typeId()!=PyIntType) {
                throw new PyException(PYILLEGALOPERATIONEXCEPTION,"range arguments must be of int type.");
            }
            if ((*args)[1]->getType()->typeId()!=PyIntType) {
                throw new PyException(PYILLEGALOPERATIONEXCEPTION,"range arguments must be of int type.");
            }
            
            start = ((PyInt*) ((*args)[1]))->getVal();
            stop = ((PyInt*) ((*args)[0]))->getVal();
            increment = 1;
            break;
        case 3:
            if ((*args)[0]->getType()->typeId()!=PyIntType) {
                throw new PyException(PYILLEGALOPERATIONEXCEPTION,"range arguments must be of int type.");
            }
            if ((*args)[1]->getType()->typeId()!=PyIntType) {
                throw new PyException(PYILLEGALOPERATIONEXCEPTION,"range arguments must be of int type.");
            }
            if ((*args)[2]->getType()->typeId()!=PyIntType) {
                throw new PyException(PYILLEGALOPERATIONEXCEPTION,"range arguments must be of int type.");
            }            
            start = ((PyInt*) ((*args)[2]))->getVal();
            stop = ((PyInt*) ((*args)[1]))->getVal();
            increment = ((PyInt*) ((*args)[0]))->getVal();
            break;
        default:
            throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Incorrect number of arguments for built-in range function.");
            break;
    }
    
    return new PyRange(start,stop,increment);
}