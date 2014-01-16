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
 * This built-in function tprint operates similarly to the fprint and 
 * print functions. Like fprint, tprint takes exactly one argument, a tuple, 
 * which can contain as many arguments as desired. Like print, the tprint
 * function returns None. There is one "tprint" function which is created
 * when CoCo starts and "tprint" is mapped to it in the globals. 
 */

#ifndef PYBUILTINTPRINT_H
#define	PYBUILTINTPRINT_H

#include "PyCallable.h"
#include "PyType.h"

class PyBuiltInTPrint : public PyCallable {
public:
    PyBuiltInTPrint();
    PyBuiltInTPrint(const PyBuiltInTPrint& orig);
    virtual ~PyBuiltInTPrint();
    PyType* getType();
    bool allowableArgCount(int count);
    string toString();
    
protected:
    virtual PyObject* __call__(vector<PyObject*>* args);
};

#endif	/* PYBUILTINTPRINT_H */

