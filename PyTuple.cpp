/* 
 * File:   PyTuple.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on March 7, 2013, 11:26 PM
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

#include "PyTuple.h"
#include "PyTupleIterator.h"
#include "PyException.h"
#include "PyInt.h"
#include "PyType.h"
#include <sstream>
using namespace std;

PyTuple::PyTuple(vector<PyObject*>* lst) : PyObject() {
    data = *lst;
    
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTuple::__getitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTuple::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTuple::__iter__);    
}

PyTuple::~PyTuple() {
}

PyType* PyTuple::getType() {
    return PyTypes[PyTupleType];
}

int PyTuple::size() {
    return data.size();
}

string PyTuple::toString() {
    ostringstream s;
    
    s << "(";
    
    for (int i=0;i<data.size();i++) {
        s << data[i]->toString();
        
        if (i < data.size()-1) 
            s << ", ";
        
    }
    
    s << ")";
    
    return s.str();
}

PyObject* PyTuple::getVal(int index) {
        if (index >= data.size()) {
        throw new PyException(PYSTOPITERATIONEXCEPTION,"Stop Iteration");
    }
    
    return data[index];
}

PyObject* PyTuple::__getitem__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyInt* intObj = (PyInt*) (*args)[0];
    
    int index = intObj->getVal();
    
    if (index >= data.size()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Index out of range.");
    }
    
    return data[index];
}

PyObject* PyTuple::__len__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    return new PyInt(data.size());
}

PyObject* PyTuple::__iter__(vector<PyObject*>* args) {
    ostringstream msg;
    
    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyTupleIterator(this);
}
