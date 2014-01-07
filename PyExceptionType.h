/* 
 * File:   PyExceptionType.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on April 6, 2013, 10:24 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * With most types, when you call the type, as in int(x) you are trying
 * to convert x to an integer. The way this is accomplished is to call the
 * magic method __int__ on the object x. However, with exceptions, when you
 * write Exception("message") or other value passed to an exception, you 
 * want to create an exception, not convert "message" to an exception by
 * calling __exception__. Because of this special handling we have a separate
 * exception type. 
 */

#ifndef PYEXCEPTIONTYPE_H
#define	PYEXCEPTIONTYPE_H

#include "PyType.h"
#include <string>
using namespace std;

class PyExceptionType : public PyType {
public:
    PyExceptionType(string typeString, PyTypeId id);
    virtual ~PyExceptionType();
    bool allowableArgCount(int count); 
    
protected:
    PyObject* __call__(vector<PyObject*>* args); 
};

#endif	/* PYEXCEPTIONTYPE_H */

