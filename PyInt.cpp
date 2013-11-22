/* 
 * File:   PyInt.cpp
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

#include "PyInt.h"
#include "PyType.h"
#include "PyStr.h"
#include "PyBool.h"
#include "PyFloat.h"
#include "PyException.h"
#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;

PyInt::PyInt(int val) {
    this->val = val;
}

PyInt::PyInt(const PyInt& orig) {
    this->val = orig.val;
}

PyInt::~PyInt() {
}

string PyInt::toString() {
    stringstream ss;
    ss << val;
    return ss.str();
}

int PyInt::getVal() {
    return val;
}

PyObject* PyInt::__add__(vector<PyObject*>* args) {
    PyInt* x;
    PyFloat* y;

    PyObject* arg = (*args)[0];

    switch (arg->getType()->typeId()) {
        case PyIntType:
            x = (PyInt*) arg;
            return new PyInt(this->val + x->val);
        case PyFloatType:
            y = (PyFloat*) arg;
            return new PyFloat(this->val + y->getVal());
        default:
            throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid types for +: int and " + arg->getType()->toString());
    }
}

PyObject* PyInt::__sub__(vector<PyObject*>* args) {
    PyInt* x;
    PyFloat* y;

    PyObject* arg = (*args)[0];

    switch (arg->getType()->typeId()) {
        case PyIntType:
            x = (PyInt*) arg;
            return new PyInt(this->val - x->val);
        case PyFloatType:
            y = (PyFloat*) arg;
            return new PyFloat(this->val - y->getVal());
        default:
            throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid types for -: int and " + arg->getType()->toString());
    }
}

PyObject* PyInt::__mul__(vector<PyObject*>* args) {
    PyInt* x;
    PyFloat* y;

    PyObject* arg = (*args)[0];

    switch (arg->getType()->typeId()) {
        case PyIntType:
            x = (PyInt*) arg;
            return new PyInt(this->val * x->val);

        case PyFloatType:
            y = (PyFloat*) arg;
            return new PyFloat(this->val * y->getVal());

        default:
            throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid types for *: int and " + arg->getType()->toString());
    }
}

PyObject* PyInt::__truediv__(vector<PyObject*>* args) {
    PyInt* x;
    PyFloat* y;

    PyObject* arg = (*args)[0];

    switch (arg->getType()->typeId()) {
        case PyIntType:
            x = (PyInt*) arg;
            if (x->val == 0)
                throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Division By Zero Error");
            return new PyFloat(this->val / x->val);

        case PyFloatType:
            y = (PyFloat*) arg;
            if (y->getVal() == 0)
                throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Division By Zero Error");
            return new PyFloat(this->val / y->getVal());

        default:
            throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid types for *: int and " + arg->getType()->toString());
    }
}

PyObject* PyInt::__floordiv__(vector<PyObject*>* args) {
    PyInt* x;
    PyFloat* y;

    PyObject* arg = (*args)[0];

    switch (arg->getType()->typeId()) {
        case PyIntType:
            x = (PyInt*) arg;
            if (x->val == 0)
                throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Division By Zero Error");
            return new PyInt(this->val / x->val);

        case PyFloatType:
            y = (PyFloat*) arg;
            if (y->getVal() == 0)
                throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Division By Zero Error");

            return new PyFloat(floor(this->val / y->getVal()));

        default:
            throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid types for *: int and " + arg->getType()->toString());
    }
}

PyObject* PyInt::__eq__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid number of arguments for int equal op.");
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val == other->val);
}

PyObject* PyInt::__lt__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid number of arguments for int equal op.");
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val < other->val);
}


PyObject* PyInt::__gt__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid number of arguments for int equal op.");
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val > other->val);
}


PyObject* PyInt::__le__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid number of arguments for int equal op.");
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val <= other->val);
}


PyObject* PyInt::__ge__(vector<PyObject*>* args) {
    if (args->size() != 1) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid number of arguments for int equal op.");
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val >= other->val);
}

PyType* PyInt::getType() {
    return PyTypes[PyIntType];
}

PyObject* PyInt::__float__(vector<PyObject*>* args) {
    return new PyFloat(this->getVal());
}

PyObject* PyInt::__int__(vector<PyObject*>* args) {
    return this;
}

PyObject* PyInt::__bool__(vector<PyObject*>* args) {
    if (this->getVal() == 0)
        return new PyBool(false);

    return new PyBool(true);
}