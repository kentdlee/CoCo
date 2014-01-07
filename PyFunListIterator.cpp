/* 
 * File:   PyListIterator.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 27, 2013, 9:36 PM
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

#include "PyFunListIterator.h"
#include "PyFunList.h"
#include "PyException.h"
#include <sstream>
#include <string>
using namespace std;

PyFunListIterator::PyFunListIterator(PyFunList* lst) : PyObject() {
    this->elm = lst->getElm();
  
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunListIterator::__iter__);
    dict["__next__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunListIterator::__next__);
}

PyFunListIterator::~PyFunListIterator() {
}

PyType* PyFunListIterator::getType() {
    return PyTypes[PyFunListIteratorType];
}

string PyFunListIterator::toString() {
    ostringstream s;
    
    s << "<funlist_iterator object at " << this << ">";
    
    return s.str();
}

PyObject* PyFunListIterator::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return this;
}

PyObject* PyFunListIterator::__next__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    if (elm == NULL) {
        throw new PyException(PYSTOPITERATIONEXCEPTION, "Stopping Iteration");
    }
    
    PyObject* item = elm->getHead();
    elm = elm->getTail();
    return item;
}
