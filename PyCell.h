/* 
 * File:   PyCell.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on March 8, 2013, 11:15 AM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * A PyCell is an object in CoCo that provides a reference to another PyObject. 
 * This provides a way of having indirect references to variables. This is
 * needed when an object is not in the local scope of a function. A PyCell 
 * (i.e. a reference) is created that points to the object in its context, that
 * is its own stack frame. These variables that are not in the local scope of a
 * function are called free variables, or FreeVars, in the CoCo.
 * 
 * When a local variable is referenced FROM another context (i.e. another 
 * function), it is also referenced by a PyCell object. This is needed so there
 * is consistency in the way the variable is referenced. The list of CellVars 
 * in a function is the list of all variables that are referenced by some other
 * function. 
 * 
 * The method deref dereferences the cell, returning the object that it refers
 * to. The set method allows the cell to be redirected to a new object. 
 */

#ifndef PYCELL_H
#define	PYCELL_H

#include "PyObject.h"
#include "PyType.h"

class PyCell : public PyObject {
public:
    PyCell(PyObject* ref);
    virtual ~PyCell();
    PyObject* deref();
    void set(PyObject* ref);
    PyType* getType();
    
private:
    PyObject* ref;

};

#endif	/* PYCELL_H */

