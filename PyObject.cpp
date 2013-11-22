/*
 * PyObject.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on: Feb 3, 2013
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyObject.h"
#include "PyException.h"
#include "PyStr.h"
#include <iostream>
using namespace std;

ostream &operator <<(ostream &os, PyObject &t) {
    return os << t.toString();
}

PyObject::PyObject() {
}

PyObject::~PyObject() {
}

PyType* PyObject::getType() {
    return NULL;
}

string PyObject::toString() {
    return "PYObject()";
}

void PyObject::incRef() {
    refCount++;
}

void PyObject::decRef() {
    refCount--;
}

int PyObject::getRefCount() const {
    return refCount;
}

bool PyObject::isCallable() const {
    return false;
}

PyObject* PyObject::__str__(vector<PyObject*>* args) {
    return new PyStr(toString());
}

PyObject* PyObject::__type__(vector<PyObject*>* args) {
    return (PyObject*)this->getType();
}

PyObject* PyObject::__cmp__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__eq__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ne__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__lt__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__gt__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__le__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ge__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__pos__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__neg__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__abs__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__invert__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__round__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__floor__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ceil__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__trunc__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__add__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__sub__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__mul__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__floordiv__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__div__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__truediv__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__mod__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__divmod__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__pow__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__lshift__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rshift__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__and__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__or__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__xor__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__radd__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rsub__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rmul__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rfloordiv__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rdiv__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rtruediv__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rmod__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rdivmod__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rpow__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rlshift__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rrshift__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rand__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ror__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__rxor__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__iadd__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__isub__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__imul__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ifloordiv__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__idiv__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__itruediv__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__imod__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ipow__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ilshift__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__iand__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ior__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__ixor__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__int__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__long__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__float__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__bool__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__cmplex__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
} // editor didn't like __complex__, c++?

PyObject* PyObject::__oct__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__hex__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__index__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__coerce__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__repr__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__unicode__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__format__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__hash__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__nonzero__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__dir__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__sizeof__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__getattr__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__setattr__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__delattr__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__getattribute__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__len__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__getitem__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__setitem__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__delitem__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__reversed__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__contains__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__missing__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__instancecheck__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__subclasscheck__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__call__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__copy__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__deepcopy__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");
}

PyObject* PyObject::__iter__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::__next__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::split(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::append(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::head(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::tail(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::concat(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::__excmatch__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::__list__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}

PyObject* PyObject::__funlist__(vector<PyObject*>* args) {
    throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Unsupported Operation");    
}
