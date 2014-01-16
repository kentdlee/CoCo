/* 
 * File:   PyBuiltInLen.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 28, 2013, 10:57 AM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * This is the built-in len function. It is called on a sequence of some sort. 
 * The len function calls the __len__ attribute (i.e. method) of the type of 
 * its argument. In this way the type controls the behavior of the len 
 * built-in function. 
 */

#ifndef PYBUILTINLEN_H
#define	PYBUILTINLEN_H

#include "PyCallable.h"
#include "PyType.h"

class PyBuiltInLen : public PyCallable {
public:
    PyBuiltInLen();
    PyBuiltInLen(const PyBuiltInLen& orig);
    virtual ~PyBuiltInLen();
    PyType* getType();
    bool allowableArgCount(int count);
    string toString();
    
protected:
    virtual PyObject* __call__(vector<PyObject*>* args);
};

#endif	/* PYBUILTINLEN_H */

