/* 
 * File:   PyBuiltInTPrint.cpp
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

#include "PyBuiltInTPrint.h"
#include "PyNone.h"
#include "PyException.h"
#include "PyTuple.h"
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

PyBuiltInTPrint::PyBuiltInTPrint() : PyCallable() {
}

PyBuiltInTPrint::PyBuiltInTPrint(const PyBuiltInTPrint& orig) {
}

PyBuiltInTPrint::~PyBuiltInTPrint() {
}

PyType* PyBuiltInTPrint::getType() {
    return PyTypes[PyBuiltInType];
}

string process(string s) {
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

PyObject* PyBuiltInTPrint::__call__(vector<PyObject*>* args) {
    //cerr << "In print() with " << args->size() << " args to print." <<  endl;
    string output = "";
    PyObject* x;
    PyObject* w;
    vector<PyObject*>* strargs = new vector<PyObject*>();
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }

    PyObject* arg = (*args)[0];


    if (arg->getType()->typeId() == PyTupleType) {
        PyTuple* tup = (PyTuple*) arg;

        for (int i = tup->size() - 1; i >= 0; i--) {
            x = tup->getVal(i);
            w = x->callMethod("__str__", strargs);
            if (x->getType()->typeId() == PyStrType)
                output = process(w->toString()) + output;
            else
                output = w->toString() + output;

            if (i > 0) {
                output = " " + output;
            }
        }
    } else {
        output = arg->toString();
    }



    cout << output << endl;

    return new PyNone();
}

string PyBuiltInTPrint::toString() {
    return "tprint";
}