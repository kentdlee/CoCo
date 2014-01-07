/* 
 * File:   PyRangeIterator.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 23, 2013, 10:51 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyRangeIterator objects are created and returned when a PyRange object 
 * is about to be iterated over. The PyRangeIterator lazily returns only 
 * the next needed integer in the range iteration. This avoids creating 
 * the whole list of integers at once, providing what is called lazy 
 * evaluation of ranges. 
 */

#ifndef PYRANGEITERATOR_H
#define	PYRANGEITERATOR_H

#include "PyType.h"
#include "PyRange.h"

class PyRangeIterator : public PyObject {
public:
    PyRangeIterator(PyRange* rangeObj);
    virtual ~PyRangeIterator();
    PyType* getType();
    string toString();
   
protected:
    PyRange* rangeObj;
    int index;
    
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __next__(vector<PyObject*>* args);
    
};

#endif	/* PYRANGEITERATOR_H */

