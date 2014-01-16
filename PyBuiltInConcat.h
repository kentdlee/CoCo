/* 
 * File:   PyBuiltInConcat.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on April 25, 2013, 11:27 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyBuiltinConcat is a built-in function (i.e. PyCallable) for the 
 * CoCo concat functionality. This built-in function takes an argument and 
 * calls the "concat" attribute that is associated with the type of the 
 * argument. Currently, only PyFunList objects support concatenation. List
 * elements must be concatable. Likely the elements of the PyFunList are 
 * strings which can be concatenated.  
 */

#ifndef PYBUILTINCONCAT_H
#define	PYBUILTINCONCAT_H


#include "PyCallable.h"
#include "PyType.h"

class PyBuiltInConcat : public PyCallable {
public:
    PyBuiltInConcat();
    PyBuiltInConcat(const PyBuiltInConcat& orig);
    virtual ~PyBuiltInConcat();
    PyType* getType();
    bool allowableArgCount(int count);
    string toString();
    
protected:
    virtual PyObject* __call__(vector<PyObject*>* args);
};


#endif	/* PYBUILTINCONCAT_H */

