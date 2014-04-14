/* 
 * File:   PyCallable.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 17, 2013, 12:21 AM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyCallable is an abstract base class for callable objects in CoCo. You 
 * can tell it is an abstract base class because allowableArgCount is set
 * to 0 in the declaration below. Setting a method to zero means that no 
 * instance of this class can ever be created, which is the definition of an
 * abstract base class. 
 * 
 * The CALL_FUNCTION instruction has an operand indicating the number of 
 * arguments to the instruction. The instruction expects there to be operand 
 * many arguments on the top of the operand stack. Just below the arguments 
 * is the callable object. The object is popped and if the number of arguments 
 * is not allowable, an exception is raised. 
 * 
 * The callName method, another abstract method, is implemented by subclasses
 * and is used if an exception is thrown to provide more information about the 
 * offending code. In other words, this method helps in debugging. 
 */

#ifndef PYCALLABLE_H
#define	PYCALLABLE_H

#include "PyObject.h"
#include <string>
using namespace std;

class PyCallable : public PyObject {
public:
    PyCallable();
    PyCallable(const PyCallable& orig);
    virtual ~PyCallable();
    
protected:
    virtual PyObject* __call__(vector<PyObject*>* args) = 0;

};

#endif	/* PYCALLABLE_H */

