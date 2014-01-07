/* 
 * File:   PyRangeType.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 23, 2013, 10:50 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * The PyRangeType is the type of ranges. The range type may be called, like
 * other types. Normally, when a type is called, like int(x) for instance, the
 * __int__ method is subsequently called on the object x. With range objects, 
 * when range(x) is called, a new range object is created to iterate from 0
 * to x-1. The range type may be called in one of several different ways with
 * arguments range(start, stop, increment). Both start and increment are 
 * optional and default to 0 and 1, respectively. 
 * 
 * Because of this different behavior when the range type is called, the
 * PyType implementation won't suffice to represent the range type. Instead,
 * this class is defined with its own special type behavior. That is, when 
 * the range type is called, a new range object is created and returned. 
 */

#ifndef PYRANGETYPE_H
#define	PYRANGETYPE_H

#include "PyType.h"
#include <string>
using namespace std;

class PyRangeType : public PyType {
public:
    PyRangeType(string typeString, PyTypeId id);
    virtual ~PyRangeType();
    bool allowableArgCount(int count);
    
protected:
    virtual PyObject* __call__(vector<PyObject*>* args);
};

#endif	/* PYRANGETYPE_H */

