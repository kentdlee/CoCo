/* 
 * File:   PyList.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 27, 2013, 9:12 PM
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

#include "PyList.h"
#include "PyListIterator.h"
#include "PyException.h"
#include "PyNone.h"
#include "PyInt.h"
#include <sstream>
using namespace std;

PyList::PyList(vector<PyObject*>* lst) : PyObject() {
    data = *lst;
   
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyList::__getitem__);
    dict["__setitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyList::__setitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyList::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyList::__iter__);
    dict["append"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyList::append);
}

PyList::~PyList() {
}

PyType* PyList::getType() {
    return PyTypes[PyListType];
}

void PyList::setVal(int index, PyObject* obj) {
    data[index] = obj;
}

string PyList::toString() {
    ostringstream s;
    
    s << "[";
    
    for (int i=0;i<data.size();i++) {
        s << data[i]->toString();
        
        if (i < data.size()-1) 
            s << ", ";
        
    }
    
    s << "]";
    
    return s.str();
}

PyObject* PyList::getVal(int index) {
        if (index >= data.size()) {
        throw new PyException(PYSTOPITERATIONEXCEPTION,"Stop Iteration");
    }
    
    return data[index];
}

PyObject* PyList::__getitem__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyInt* intObj = (PyInt*) (*args)[0];
    
    int index = intObj->getVal();
    
    if (index >= data.size()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Index out of range.");
    }
    
    return data[index];
}

PyObject* PyList::__setitem__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 2) {
        msg << "TypeError: expected 2 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyInt* intObj = (PyInt*) (*args)[0];
    
    int index = intObj->getVal();
    
    if (index >= data.size()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Index out of range.");
    }
    
    data[index] = (*args)[1];
    
    return new PyNone();
}

PyObject* PyList::__len__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyInt(data.size());
}

PyObject* PyList::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {        
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyListIterator(this);
}

PyObject* PyList::append(vector<PyObject*>* args) {
    PyObject* obj = (*args)[0];
    
    data.push_back(obj);
    
    return new PyNone();   
}