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

PyInt::PyInt(int val): PyObject() {
    this->val = val;
    dict["__add__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__add__);
    dict["__sub__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__sub__);
    dict["__mul__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__mul__);
    dict["__floordiv__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__floordiv__);
    dict["__truediv__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__truediv__);
    dict["__eq__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__eq__);
    dict["__gt__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__gt__);
    dict["__lt__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__lt__);
    dict["__ge__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__ge__);
    dict["__le__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__le__);
    dict["__float__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__float__);
    dict["__int__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__int__);
    dict["__bool__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyInt::__bool__);
}

PyInt::PyInt(const PyInt& orig) : PyInt(orig.val) {
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
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
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
    ostringstream msg;
    
    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
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
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
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
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyObject* arg = (*args)[0];

    switch (arg->getType()->typeId()) {
        case PyIntType:
            x = (PyInt*) arg;
            if (x->val == 0)
                throw new PyException(PYILLEGALOPERATIONEXCEPTION, "ZeroDivisionError: integer division or modulo by zero");
            return new PyFloat(this->val / x->val);

        case PyFloatType:
            y = (PyFloat*) arg;
            if (y->getVal() == 0)
                throw new PyException(PYILLEGALOPERATIONEXCEPTION, "ZeroDivisionError: integer division or modulo by zero");
            return new PyFloat(this->val / y->getVal());

        default:
            throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid types for *: int and " + arg->getType()->toString());
    }
}

PyObject* PyInt::__floordiv__(vector<PyObject*>* args) {
    PyInt* x;
    PyFloat* y;
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyObject* arg = (*args)[0];

    switch (arg->getType()->typeId()) {
        case PyIntType:
            x = (PyInt*) arg;
            if (x->val == 0)
                throw new PyException(PYILLEGALOPERATIONEXCEPTION, "ZeroDivisionError: integer division or modulo by zero");
            return new PyInt(this->val / x->val);

        case PyFloatType:
            y = (PyFloat*) arg;
            if (y->getVal() == 0)
                throw new PyException(PYILLEGALOPERATIONEXCEPTION, "ZeroDivisionError: integer division or modulo by zero");

            return new PyFloat(floor(this->val / y->getVal()));

        default:
            throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Invalid types for *: int and " + arg->getType()->toString());
    }
}

PyObject* PyInt::__eq__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val == other->val);
}

PyObject* PyInt::__lt__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val < other->val);
}


PyObject* PyInt::__gt__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val > other->val);
}


PyObject* PyInt::__le__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val <= other->val);
}


PyObject* PyInt::__ge__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }

    //We should check the type of args[0] before casting it. 
    PyInt* other = (PyInt*) (*args)[0];

    return new PyBool(val >= other->val);
}

PyType* PyInt::getType() {
    return PyTypes[PyIntType];
}

PyObject* PyInt::__float__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyFloat(this->getVal());
}

PyObject* PyInt::__int__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return this;
}

PyObject* PyInt::__bool__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    if (this->getVal() == 0)
        return new PyBool(false);

    return new PyBool(true);
}