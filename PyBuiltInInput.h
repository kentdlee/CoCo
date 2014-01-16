/* 
 * File:   PyBuiltInInput.h
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
 * This is the built-in input function from Python. It takes one argument, 
 * a string prompt, and returns a string read from standard input. Only one of
 * these objects is created when CoCo starts and "input" is mapped to it in the
 * globals. 
 */

#ifndef PYBUILTININPUT_H
#define	PYBUILTININPUT_H

#include "PyCallable.h"
#include "PyType.h"


class PyBuiltInInput : public PyCallable {
public:
    PyBuiltInInput();
    PyBuiltInInput(const PyBuiltInInput& orig);
    virtual ~PyBuiltInInput();
    PyType* getType();

    bool allowableArgCount(int count);
    string toString();
protected:
    virtual PyObject* __call__(vector<PyObject*>* args);

};

#endif	/* PYBUILTININPUT_H */

