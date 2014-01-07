/* 
 * File:   PyList.h
 * Author: Kent D. Lee
 * (c)
 * Created on February 27, 2013, 9:12 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyFunList objects are lists where the head and the tail are joined 
 * together to form a list in the same manner that most functional languages
 * implement lists. This formulation of a list enables O(1) head and tail
 * (i.e. car and cdr if you are a Lisp programmer) operations. 
 */

#ifndef PYFUNLIST_H
#define	PYFUNLIST_H

#include "PyObject.h"
#include "PyType.h"
#include <vector>
using namespace std;

class PyFunListElm;

class PyFunList : public PyObject {
public:
    PyFunList(vector<PyObject*>* lst);
    PyFunList();
    PyFunList(PyObject* head, PyFunList* tail);
    PyFunList(PyFunListElm* elm);
    virtual ~PyFunList();
    PyType* getType();
    string toString();
    PyObject* getHead();
    PyFunList* getTail();
    PyFunListElm* getElm(); /* Used ONLY by PyFunListIterator (should be friend) */
    

    
    
protected:
    PyFunListElm* data;
    virtual PyObject* __getitem__(vector<PyObject*>* args);
    virtual PyObject* __len__(vector<PyObject*>* args);
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __add__(vector<PyObject*>* args);
    virtual PyObject* head(vector<PyObject*>* args);
    virtual PyObject* tail(vector<PyObject*>* args);
    virtual PyObject* concat(vector<PyObject*>* args);
};

class PyFunListElm {
public:
    PyFunListElm(PyObject* head, PyFunListElm* tail);
    ~PyFunListElm();
    string toString();
    PyObject* getHead();
    PyFunListElm* getTail();
    int getLen();
    
private:
    PyObject* head;
    PyFunListElm* tail;
    int len;
};

#endif	/* PYFUNLIST_H */

