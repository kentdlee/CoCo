/* 
 * File:   PyBuiltInPrint.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 16, 2013, 8:26 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * The built-in print function converts each of its arguments to strings by
 * calling the __str__ attribute (i.e. method) on each of its arguments. In 
 * this way, the type of each argument controls how the argument is converted 
 * to a string. There is one PyBuiltInPrint object created and "print" is 
 * mapped to it in the globals. 
 */

#ifndef PYBUILTINPRINT_H
#define	PYBUILTINPRINT_H

#include "PyCallable.h"
#include "PyType.h"

class PyBuiltInPrint : public PyCallable {
public:
    PyBuiltInPrint();
    PyBuiltInPrint(const PyBuiltInPrint& orig);
    virtual ~PyBuiltInPrint();
    PyType* getType();
    bool allowableArgCount(int count);
    string toString();
    
private:
    PyObject* __call__(vector<PyObject*>* args);
};

#endif	/* PYBUILTINPRINT_H */

