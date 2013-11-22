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

#include "PyListIterator.h"
#include <sstream>
#include <string>
using namespace std;

PyListIterator::PyListIterator(PyList* lst) {
    this->index = 0;
    this->lst = lst;
}

PyListIterator::~PyListIterator() {
}

PyType* PyListIterator::getType() {
    return PyTypes[PyListIteratorType];
}

string PyListIterator::toString() {
    ostringstream s;
    
    s << "<list_iterator object at " << this << ">";
    
    return s.str();
}

PyObject* PyListIterator::__iter__(vector<PyObject*>* args) {
    return this;
}

PyObject* PyListIterator::__next__(vector<PyObject*>* args) {
    return lst->getVal(index++);
}
