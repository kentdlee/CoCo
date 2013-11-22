/* 
 * File:   PyType.cpp
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
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyObject.h"
#include "PyType.h"
#include "PyException.h"
#include "PyStr.h"
#include <iostream>
using namespace std;

PyType::PyType(string typeString, PyTypeId id) {
    this->typeString = typeString;
    this->index = id;
}

PyType::~PyType() {
}

void PyType::addFun(string name, PyFun fun, int numargs) {
    // The signature of all fun arguments must be 
    // PyObject* fun(vector<PyObject*>* args) where args is of length numargs
    dict[name] = fun;
    argcount[name] = numargs;
}

PyFun PyType::getFun(string name) {
    if (dict.find(name) == dict.end()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"operation " + name + " undefined for type " + typeString);
    }

    return dict[name];
}

int PyType::getArgCount(string name) {
    if (argcount.find(name) == argcount.end()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"operation " + name + " undefined for type " + typeString);
    }

    return argcount[name];
}

string PyType::toString() {
    return this->typeString;
}


PyType* PyType::getType() {
    return PyTypes[PyTypeType];
}

PyTypeId PyType::typeId() {
    return index;
}

bool PyType::allowableArgCount(int count) {
    // the line below was 
    // return count == 1 || count == 3;
    // but for the life of me I don't know why it would be
    // need to allow three arguments. 
    return count == 1;
}

string PyType::callName() {
    return "type";
}

/* The following method is called when calling one of the magic methods
 * on an instance of this type. Only magic methods that are defined 
 * in the dictionary are allowed. Magic methods are added to the dictionary
 * in the initTypes function (in main.cpp) and are added by calling the addFun
 * method above.                             
 */

PyObject* PyType::call(string name, PyObject* self, vector<PyObject*>* args) {
    if (dict.find(name) == dict.end()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"operation " + name + " undefined for type " + typeString);
    }

    //cerr << "argcount of " << name << " is " << argcount[name] << " for type " << typeString << endl;
    
    if ((argcount[name] > 0) && (argcount[name] != (args->size() + 1))) {
        //if argcount is zero then number of arguments is variable and must be 
        //checked by the called method.
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"operation " + name + " given incorrect number of arguments.");
    }

    return ((*self).*dict[name])(args);
}

PyObject* PyType::__str__(vector<PyObject*>* args) {
    return new PyStr("<class '" +toString()+"'>");
}

PyObject* PyType::__type__(vector<PyObject*>* args) {
    return PyTypes[PyTypeType];
}

/* Not to be confused with the call method above, the __call__ method is called
 * by call when the type is called as in int(x) for example. Type conversion is
 * handled by calling the __bool__, __int__, __float__, or __str__ method on 
 * the instance's class. A byproduct of this is that __type__ can get called 
 * on objects within the system. The __type__ magic method was added for this 
 * implementation to support the implementation of __call__ below. When __type__
 * is called on a non-type object it is handled in the PyObject class by 
 * returning the type of the object. When called on a type, the __type__ function
 * returns the instance of the type "type" (seen above). This is exactly as 
 * the real Python interpreter behaves. 
 */

PyObject* PyType::__call__(vector<PyObject*>* args) {
    vector<PyObject*>* emptyArgs = new vector<PyObject*>();
    PyObject* arg = (*args)[0];
    string funName = "__"+this->toString()+"__";
    return arg->getType()->call(funName,arg,emptyArgs);
}