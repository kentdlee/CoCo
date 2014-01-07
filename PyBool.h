/* 
 * File:   PyBool.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 16, 2013, 4:05 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyBool objects are the CoCo implementation of boolean values. 
 */

#ifndef PYBOOL_H
#define	PYBOOL_H

#include "PyType.h"
#include "PyCallable.h"
#include <string>
using namespace std;

class PyBool : public PyObject {
public:
    PyBool();
    PyBool(bool val);
    PyBool(const PyBool& orig);
    virtual ~PyBool();
    
    PyType* getType();
    string toString();
    bool getVal();


protected:
    bool val;

    virtual PyObject* __float__(vector<PyObject*>* args);
    virtual PyObject* __int__(vector<PyObject*>* args);
    virtual PyObject* __bool__(vector<PyObject*>* args);
    virtual PyObject* __eq__(vector<PyObject*>* args);
};

#endif	/* PYBOOL_H */

