/* 
 * File:   PyList.h
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
 * The PyList class implements lists similarly to the way they are 
 * implemented in Python. PyLists have O(1) access time to any element
 * of the list. They are implemented using the C++ vector so they exhibit
 * the same characteristics and running time as similar methods on C++ 
 * vectors. For instance, appending to a PyList has the same running
 * time as the push_back C++ vector method. 
 */

#ifndef PYLIST_H
#define	PYLIST_H

#include "PyObject.h"
#include "PyType.h"
#include <vector>
using namespace std;

class PyList : public PyObject {
public:
    PyList(vector<PyObject*>* lst);
    virtual ~PyList();
    PyType* getType();
    string toString();
    PyObject* getVal(int index);
    void setVal(int index, PyObject* val);
    

    
protected:
    vector<PyObject*> data;

    virtual PyObject* __getitem__(vector<PyObject*>* args);
    virtual PyObject* __setitem__(vector<PyObject*>* args);
    virtual PyObject* __len__(vector<PyObject*>* args);
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* append(vector<PyObject*>* args);
};

#endif	/* PYLIST_H */

