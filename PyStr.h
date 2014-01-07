/* 
 * File:   PyStr.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 12, 2013, 10:14 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * A PyStr object is a string in CoCo. We can do lots of things with 
 * strings as is evident by the overridden magic methods below and the
 * split method. CoCo strings are implemented using the C++ string class
 * so many of these methods are pretty simple to implement. 
 */

#ifndef PYSTR_H
#define	PYSTR_H
class PyObject;

#include "PyCallable.h"
#include <string>
using namespace std;

class PyStr : public PyObject {
public:
    PyStr(string s);
    PyStr(const PyStr& orig);
    virtual ~PyStr();
    PyType* getType();
    string toString();
    PyStr* charAt(int index);

protected:
    string val;
    
    PyObject* __add__(vector<PyObject*>* args);
    PyObject* __str__(vector<PyObject*>* args);
    PyObject* __float__(vector<PyObject*>* args);
    PyObject* __int__(vector<PyObject*>* args);
    PyObject* __bool__(vector<PyObject*>* args); 
    PyObject* __funlist__(vector<PyObject*>* args); 
    PyObject* __eq__(vector<PyObject*>* args);
    PyObject* split(vector<PyObject*>* args);
    
    PyObject* __getitem__(vector<PyObject*>* args);
    PyObject* __len__(vector<PyObject*>* args);
    PyObject* __iter__(vector<PyObject*>* args);
};

#endif	/* PYSTR_H */

