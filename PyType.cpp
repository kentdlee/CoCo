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
#include <sstream>
using namespace std;

PyType::PyType(string typeString, PyTypeId id) : PyCallable() {
    this->typeString = typeString;
    this->index = id;
}

PyType::~PyType() {
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

string PyType::callName() {
    return "type";
}

/* The following method is called when calling one of the magic methods
 * on an instance of this type. Only magic methods that are defined 
 * in the dictionary are allowed. Magic methods are added to the dictionary
 * in the initTypes function (in main.cpp) and are added by calling the addFun
 * method above.                             
 */

PyObject* PyType::__str__(vector<PyObject*>* args) {
    return new PyStr("<class '" +toString()+"'>");
}

PyObject* PyType::__type__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return PyTypes[PyTypeType];
}

/* Not to be confused with the callMethod method, the __call__ method is called
 * by callMethod when the type is called as in int(x) for example. Type conversion is
 * handled by calling the __bool__, __int__, __float__, or __str__ method on 
 * the instance's class. A by-product of this is that __type__ can get called 
 * on objects within the system. The __type__ magic method was added for this 
 * implementation to support the implementation of __call__ below. When __type__
 * is called on a non-type object it is handled in the PyObject class by 
 * returning the type of the object. When called on a type, the __type__ function
 * returns the instance of the type "type" (seen above). This is exactly as 
 * the real Python interpreter behaves. 
 */

PyObject* PyType::__call__(vector<PyObject*>* args) {
    ostringstream msg; 
    
    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    vector<PyObject*>* emptyArgs = new vector<PyObject*>();
    PyObject* arg = (*args)[0];
    string funName = "__"+this->toString()+"__";
    return arg->callMethod(funName,emptyArgs);
}