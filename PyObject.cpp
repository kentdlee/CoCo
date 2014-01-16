/*
 * PyObject.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on: Feb 3, 2013
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

#include "PyObject.h"
#include "PyException.h"
#include "PyStr.h"
#include <iostream>
#include "PyType.h"
#include <sstream>
using namespace std;

ostream& operator <<(ostream &os, PyObject &t) {
    return os << t.toString();
}

PyObject* PyObject::callMethod(string name, vector<PyObject*>* args) {
    // This is where the magic happens. The declaration below declares mbr
    // as a member function pointer to a method that takes a pointer to a 
    // vector of PyObject pointers as its argument and returns a PyObject 
    // pointer. All magic methods and method calls in CoCo adhere to this 
    // strict function call type. 
    PyObject* (PyObject::*mbr)(vector<PyObject*>*);
    
    if (dict.find(name) == dict.end()) {
        // If we lookup the magic method and don't find it, raise an exception.
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "TypeError: '"+ getType()->toString() + "' object has no attribute '" + name + "'");
    }
    
    // Set the mbr pointer to the function's address.
    mbr = dict[name]; 
    
    // Here is how to call the function. First, mbr is a method of 
    // the current class, whether a sub-class or not. Sub-classes will 
    // automatically work with this code. So, we dereference this to get
    // into the object. Then we dereference mbr to get to the method's code
    // and finally pass the args to the method. This is very slick since
    // it works on any subclass that defines a magic method. Because all 
    // magic methods are implemented as virtual functions, this works means
    // if a base class defines a magic method, subclasses automatically pick
    // up that functionality. 
    
    return (this->*mbr)(args);
}

PyObject::PyObject() {
    dict["__str__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyObject::__str__);
    dict["__type__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyObject::__type__);
}

PyObject::~PyObject() {
}

PyType* PyObject::getType() {
    return NULL;
}

string PyObject::toString() {
    return "PyObject()";
}

void PyObject::incRef() {
    refCount++;
}

void PyObject::decRef() {
    refCount--;
}

int PyObject::getRefCount() const {
    return refCount;
}

PyObject* PyObject::__str__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyStr(toString());
}

PyObject* PyObject::__type__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return (PyObject*)this->getType();
}
