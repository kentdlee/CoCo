/* 
 * File:   PyRange.h
 * Author: Kent D. Lee
 * (c)
 * Created on February 23, 2013, 8:25 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * The PyRange object implements lazy evaluation of ranges of integers. Python
 * 2.x did not have range objects. They were added in Python 3. In Python 2.x, 
 * when the range function was called, a list of integers was returned. If
 * the list was large, all elements of the list were generated and the 
 * entire list was returned. This is inefficient, especially if the loop is 
 * exited early for some reason. In Python 3, when the range function is called, 
 * a range object is returned instead. The advantage is that the list of 
 * integers is never actually generated. Instead, when a new integer is needed, 
 * the __next__ method is called on the iterator returned by calling the __iter__
 * magic method on the PyRange object. 
 * 
 */

#ifndef PYRANGE_H
#define	PYRANGE_H

#include "PyObject.h"
#include <vector>
using namespace std;

class PyRange : public PyObject {
public:
    PyRange(int start, int stop, int increment);
    virtual ~PyRange();
    PyType* getType();

    PyObject* indexOf(int index);
    string toString();
    
protected:
    int start, stop, increment;
    
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __len__(vector<PyObject*>* args);
    virtual PyObject* __getitem__(vector<PyObject*>* args);
    virtual PyObject* __list__(vector<PyObject*>* args);
};

#endif	/* PYRANGE_H */

