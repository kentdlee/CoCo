/* 
 * File:   PyTuple.h
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
 * PyTuple objects are like PyList objects except that tuples are 
 * immutable. We can get the length of a tuple, iterate over a tuple,
 * and index into a tuple. Tuples are constructed in Python as shown 
 * below.
 * >>> t = ('a','b','c')
 * >>> type(t)
 * <class 'tuple'>
 * >>> for x in t:
 * ...   print(x)
 * ... 
 * a
 * b
 * c
 * >>> 
 */

#ifndef PYTUPLE_H
#define	PYTUPLE_H

#include "PyObject.h"

class PyTuple : public PyObject {
public:
    PyTuple(vector<PyObject*>* lst);
    virtual ~PyTuple();
    PyType* getType();
    string toString();
    PyObject* getVal(int index);
    int size();
    

    
protected:
    vector<PyObject*> data;

    virtual PyObject* __getitem__(vector<PyObject*>* args);
    virtual PyObject* __len__(vector<PyObject*>* args);
    virtual PyObject* __iter__(vector<PyObject*>* args);
};


#endif	/* PYTUPLE_H */

