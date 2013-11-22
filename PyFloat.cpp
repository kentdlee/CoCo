/* 
 * File:   PyFloat.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 12, 2013, 10:13 PM
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

#include "PyFloat.h"
#include "PyStr.h"
#include "PyInt.h"
#include "PyType.h"
#include "PyBool.h"
#include "PyException.h"
#include <sstream>
using namespace std;

PyFloat::PyFloat(double f) {
    val = f;
}

PyFloat::PyFloat(const PyFloat& orig) {
    val = orig.val;
}

PyFloat::~PyFloat() {
}

string PyFloat::toString() {
    stringstream ss;
    ss << val;
    return ss.str();
}

PyObject* PyFloat::__add__(vector<PyObject*>* args) {
    PyFloat* arg2 = (PyFloat*) (*args)[0];
    return new PyFloat(this->val + arg2->val);
}

PyType* PyFloat::getType() {
    return PyTypes[PyFloatType];
}

double PyFloat::getVal() {
    return val;
}


PyObject* PyFloat::__float__(vector<PyObject*>* args) {
    return this;
}

PyObject* PyFloat::__int__(vector<PyObject*>* args) {
    int x;
    
    x = (int)this->getVal();
    return new PyInt(x);
}

PyObject* PyFloat::__bool__(vector<PyObject*>* args) {
    if (this->getVal()==0.0)
        return new PyBool(false);
    
    return new PyBool(true);
}