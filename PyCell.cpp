/* 
 * File:   PyCell.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on March 8, 2013, 11:15 AM
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
 */

#include "PyCell.h"

PyCell::PyCell(PyObject* ref) : PyObject() {
    this->ref = ref;
}


PyCell::~PyCell() {
    try {
        delete ref;
    } catch (...) {}
}

PyObject* PyCell::deref() {
    return ref;
}

void PyCell::set(PyObject* ref) {
    this->ref = ref;
}

PyType* PyCell::getType() {
    return PyTypes[PyCellType];
}