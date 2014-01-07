/* 
 * File:   PyListIterator.h
 * Author: Kent D. Lee
 * (c)
 * Created on February 27, 2013, 9:36 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * Here we have the class that defines iterators over functional lists (i.e. 
 * PyFunList objects), so we can efficiently iterate over them. 
 * 
 */

#ifndef PYFUNLISTITERATOR_H
#define	PYFUNLISTITERATOR_H

#include "PyObject.h"
#include "PyType.h"
#include "PyFunList.h"
#include <string>
using namespace std;

class PyFunListIterator : public PyObject {
public:
    PyFunListIterator(PyFunList* lst);
    virtual ~PyFunListIterator();  
    PyType* getType();
    string toString();

protected:
    PyFunListElm* elm;

    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __next__(vector<PyObject*>* args);    

};

#endif	/* PYFUNLISTITERATOR_H */

