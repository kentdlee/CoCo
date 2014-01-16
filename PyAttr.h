/* 
 * File:   PyAttr.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 27, 2013, 5:11 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * This class defines an Attr object which is used to look up a method or 
 * other attribute of an object. The Attr object inherits from PyCallable 
 * meaning that this object once created can be called, thus providing the
 * virtual machine with a way of calling methods on objects. In Python, and
 * in the CoCo, the lookup of the method in the object happens when the call
 * occurs (i.e. dynamically). 
 * 
 */

#ifndef PYATTR_H
#define	PYATTR_H

#include "PyCallable.h"
#include <string>
using namespace std;

class PyAttr : public PyCallable {
public:
    PyAttr(PyObject* self, string method);
    virtual ~PyAttr();
    bool allowableArgCount(int count);

    PyType* getType();
    string toString();
    
protected: 
    string method;
    PyObject* self;

    virtual PyObject* __call__(vector<PyObject*>* args);
};

#endif	/* PYATTR_H */

