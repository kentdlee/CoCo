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

PyBuiltInConcat::PyBuiltInConcat() {
}

PyBuiltInConcat::PyBuiltInConcat(const PyBuiltInConcat& orig) {
}

PyBuiltInConcat::~PyBuiltInConcat() {
}

PyType* PyBuiltInConcat::getType() {
    return PyTypes[PyBuiltInType];
}

PyObject* PyBuiltInConcat::__call__(vector<PyObject*>* args) {
    PyObject* x;

    x = (*args)[0];
    
    vector<PyObject*>* callArgs = new vector<PyObject*>();
    
    PyType* selfType = x->getType();
    
    return selfType->call("concat",x,callArgs);
}

bool PyBuiltInConcat::allowableArgCount(int count) {
    return count == 1;
}

string PyBuiltInConcat::callName() {
    return "concat";
}

string PyBuiltInConcat::toString() {
    return callName();
}