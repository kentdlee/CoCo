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
 * The built-in fprint function operates like print except in two ways. The 
 * argument to fprint must be a tuple (which may contain only one item). The
 * second difference is that fprint returns an instance of itself to be used 
 * in further printing if so desired. Only one of these objects is created when
 * CoCo starts and "fprint" is mapped to it in the globals. 
 */

#ifndef PYBUILTINFPRINT_H
#define	PYBUILTINFPRINT_H

#include "PyCallable.h"
#include "PyType.h"

class PyBuiltInFPrint : public PyCallable {
public:
    PyBuiltInFPrint();
    PyBuiltInFPrint(const PyBuiltInFPrint& orig);
    virtual ~PyBuiltInFPrint();
    PyType* getType();

    bool allowableArgCount(int count);
    string toString();
    
protected:
    virtual PyObject* __call__(vector<PyObject*>* args);

};

#endif	/* PYBUILTINFPRINT_H */

