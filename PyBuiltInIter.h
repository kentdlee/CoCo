/* 
 * File:   PyBuiltInIter.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 25, 2013, 10:17 AM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * The built-in iter function returns an iterator object for its argument
 * which must be iterable. This class implements the built-in function that is
 * called when iter() is called on an iterable of some sort. This function 
 * calls the __iter__ attribute on the type of its argument. In this way
 * the type controls how the built-in iter function behaves. 
 */

#ifndef PYBUILTINITER_H
#define	PYBUILTINITER_H

#include "PyCallable.h"
#include "PyType.h"

class PyBuiltInIter : public PyCallable {
public:
    PyBuiltInIter();
    PyBuiltInIter(const PyBuiltInIter& orig);
    virtual ~PyBuiltInIter();
    
    PyType* getType();

    bool allowableArgCount(int count);
    string toString();
protected:
    virtual PyObject* __call__(vector<PyObject*>* args);
};

#endif	/* PYBUILTINITER_H */

