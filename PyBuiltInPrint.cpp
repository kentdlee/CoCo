/* 
 * File:   PyBuiltInPrint.cpp
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
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyBuiltInPrint.h"
#include "PyNone.h"
#include <vector>
#include <iostream>
using namespace std;


PyBuiltInPrint::PyBuiltInPrint() : PyCallable() {
}

PyBuiltInPrint::PyBuiltInPrint(const PyBuiltInPrint& orig) {
}

PyBuiltInPrint::~PyBuiltInPrint() {
}

PyType* PyBuiltInPrint::getType() {
    return PyTypes[PyBuiltInType];
}

PyObject* PyBuiltInPrint::__call__(vector<PyObject*>* args) {
    //cerr << "In print() with " << args->size() << " args to print." <<  endl;
    string output = "";
    PyObject* x;
    PyObject* w;
    vector<PyObject*>* strargs = new vector<PyObject*>();
    
    for (int i=0;i<args->size();i++) {
        x = (*args)[i];
        w = x->callMethod("__str__", strargs);
        output = w->toString() + output;
        
        if (i < args->size()-1) {
            output = " " + output;
        }   
    }
    
    cout << output << endl;
    
    return new PyNone();
}

string PyBuiltInPrint::toString() {
    return "print";
}