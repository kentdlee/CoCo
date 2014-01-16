/* 
 * File:   PyBuiltInFPrint.cpp
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

#include "PyBuiltInFPrint.h"
#include "PyNone.h"
#include "PyException.h"
#include "PyTuple.h"
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

PyBuiltInFPrint::PyBuiltInFPrint() : PyCallable() {
}

PyBuiltInFPrint::PyBuiltInFPrint(const PyBuiltInFPrint& orig) {
}

PyBuiltInFPrint::~PyBuiltInFPrint() {
}

PyType* PyBuiltInFPrint::getType() {
    return PyTypes[PyBuiltInType];
}

string processit(string s) {
    ostringstream ss;
    bool escape = false;

    for (int i = 0; i < s.size(); i++) {
        if (escape) {
            switch (s[i]) {
                case 'n':
                    ss << "\n";
                    break;
                case 't':
                    ss << "\t";
                    break;
                default:
                    ss << s[i];
                    break;
            }

            escape = false;

        } else {

            escape = (s[i] == '\\');

            if (!escape) {
                ss << s[i];
            }
        }
    }

    return ss.str();
}

PyObject* PyBuiltInFPrint::__call__(vector<PyObject*>* args) {
    //cerr << "In print() with " << args->size() << " args to print." <<  endl;
    string output = "";
    PyObject* x;
    PyObject* w;
    vector<PyObject*>* strargs = new vector<PyObject*>();
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());    }

    PyObject* arg = (*args)[0];
    output = arg->toString();

    if (arg->getType()->typeId()==PyStrType)
        output = processit(output);
    
    cout << output;

    return this;
}

string PyBuiltInFPrint::toString() {
    return "fprint";
}