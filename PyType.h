/* 
 * File:   PyType.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 12, 2013, 10:58 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * Most of the types in CoCo are instances of this class. The exceptions are
 * range objects are exception objects. All other types of objects share a 
 * common behavior and are instances of PyType. The main.cpp file contains 
 * the code that creates the type instances. There is one instance of each
 * different type of CoCo value. For instance, there is one instance of PyType
 * for all PyInt objects. All PyInt objects, when their type is requested (via
 * the type function) return the one instance of the PyInt type. This is found
 * by looking up the instance in the PyTypes map that is declared at the 
 * bottom of this header file. The main.cpp code initializes this map. 
 */

#ifndef PYTYPE_H
#define	PYTYPE_H

#include "PyCallable.h"
#include <string>
#include <map>
#include <vector>
using namespace std;

typedef PyObject* (PyObject::*PyFun)(vector<PyObject*>*);

enum PyTypeId {
    PyTypeType,
    PyNoneType,
    PyBoolType,
    PyIntType,
    PyFloatType,
    PyStrType,
    PyFunctionType,
    PyBuiltInType,
    PyRangeTypeId,
    PyRangeIteratorType,
    PyListType,
    PyListIteratorType,
    PyFunListType,
    PyFunListIteratorType,
    PyStrIteratorType,
    PyCodeType,
    PyTupleType,
    PyTupleIteratorType,
    PyCellType,
    PyExceptionTypeId           
};

class PyType : public PyCallable {
public:
    PyType(string typeString, PyTypeId id);
    virtual ~PyType();
    void addFun(string name, PyFun fun, int numargs);
    PyFun getFun(string name);
    int getArgCount(string name);
    PyObject* call(string name, PyObject* self, vector<PyObject*>* args);
    string toString();
    PyType* getType();
    PyTypeId typeId();
    bool allowableArgCount(int count);
    string callName();
    PyObject* __call__(vector<PyObject*>* args);
    PyObject* __str__(vector<PyObject*>* args);
    PyObject* __type__(vector<PyObject*>* args);
    
private:
    string typeString;
    PyTypeId index;
    map<string, PyFun> dict;
    map<string, int> argcount;
};

extern map<PyTypeId, PyType*> PyTypes;

#endif	/* PYTYPE_H */

