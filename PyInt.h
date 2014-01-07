/* 
 * File:   PyInt.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 12, 2013, 10:13 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyInt objects are limited to 32-bit or native ints in the CoCo unlike 
 * Python which allows arbitrarily large integers in its implementation. 
 */

#ifndef PYINT_H
#define	PYINT_H

#include "PyCallable.h"
#include <vector> 
using namespace std;

class PyInt : public PyObject {
public:
    PyInt(int val);
    PyInt(const PyInt& orig);
    virtual ~PyInt();
    PyType* getType();
    string toString();
    int getVal();
    
protected:
    int val;
    
    virtual PyObject* __add__(vector<PyObject*>* args);
    virtual PyObject* __sub__(vector<PyObject*>* args);
    virtual PyObject* __mul__(vector<PyObject*>* args);
    virtual PyObject* __floordiv__(vector<PyObject*>* args);
    virtual PyObject* __truediv__(vector<PyObject*>* args);
    virtual PyObject* __eq__(vector<PyObject*>* args);
    virtual PyObject* __gt__(vector<PyObject*>* args);
    virtual PyObject* __lt__(vector<PyObject*>* args);
    virtual PyObject* __ge__(vector<PyObject*>* args);
    virtual PyObject* __le__(vector<PyObject*>* args);
    virtual PyObject* __float__(vector<PyObject*>* args);
    virtual PyObject* __int__(vector<PyObject*>* args);
    virtual PyObject* __bool__(vector<PyObject*>* args);
};

#endif	/* PYINT_H */

