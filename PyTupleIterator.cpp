/* 
 * File:   PyTupleIterator.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on March 7, 2013, 11:37 PM
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

#include "PyTupleIterator.h"
#include "PyException.h"
#include <sstream>
#include <string>
using namespace std;

PyTupleIterator::PyTupleIterator(PyTuple* lst) : PyObject() {
    this->index = 0;
    this->lst = lst;
    
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTupleIterator::__iter__);
    dict["__next__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyTupleIterator::__next__);
}

PyTupleIterator::~PyTupleIterator() {
}

PyType* PyTupleIterator::getType() {
    return PyTypes[PyTupleIteratorType];
}

string PyTupleIterator::toString() {
    ostringstream s;
    
    s << "<tuple_iterator object at " << this << ">";
    
    return s.str();
}

PyObject* PyTupleIterator::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());
    }
    
    return this;
}

PyObject* PyTupleIterator::__next__(vector<PyObject*>* args) {
    ostringstream msg; 
    
    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());
    }
    
    return lst->getVal(index++);
}

