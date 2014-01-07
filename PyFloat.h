/* 
 * File:   PyFloat.h
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
 * This class defines the floating point numnbers of CoCo. While the type is
 * called float, the values are actually doubles as shown below. 
 */

#ifndef PYFLOAT_H
#define	PYFLOAT_H

#include "PyCallable.h"

class PyFloat : public PyObject {
public:
    PyFloat(double f);
    PyFloat(const PyFloat& orig);
    virtual ~PyFloat();
    string toString();
    PyType* getType();
    double getVal();

protected:
    double val;

    virtual PyObject* __add__(vector<PyObject*>* args);
    virtual PyObject* __float__(vector<PyObject*>* args);
    virtual PyObject* __int__(vector<PyObject*>* args);
    virtual PyObject* __bool__(vector<PyObject*>* args);
};

#endif	/* PYFLOAT_H */

