/* 
 * File:   PyStr.cpp
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
 * See the associated header file for a description of the purpose of this 
 * class. Implementation details are provided here. Read below for 
 * any specific details. 
 * 
 */

#include "PyStr.h"
#include "PyType.h"
#include "PyFloat.h"
#include "PyInt.h"
#include "PyBool.h"
#include "PyException.h"
#include "PyStrIterator.h"
#include "PyList.h"
#include "PyFunList.h"
#include <sstream>
using namespace std;

PyStr::PyStr(string s) : PyObject() {
    val = s;
    
    dict["__add__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__add__);
    dict["__float__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__float__);
    dict["__int__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__int__);
    dict["__bool__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__bool__);
    dict["__funlist__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__funlist__);
    dict["__eq__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__eq__);
    dict["split"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::split);
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__getitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyStr::__iter__);
}

PyStr::PyStr(const PyStr& orig) : PyStr(orig.val) {
}

PyStr::~PyStr() {
}

PyObject* PyStr::__add__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyStr* arg = (PyStr*) (*args)[0];
    return new PyStr(this->val + arg->val);
}

PyObject* PyStr::__str__(vector<PyObject*>* args) {
    return this;
}

PyObject* PyStr::__float__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    double x;
    try {
        istringstream in(this->toString());
        in.exceptions(ios_base::failbit | ios_base::badbit);
        in >> x;
        return new PyFloat(x);
    } catch (...) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"could not convert string to float: '"+this->toString()+"'");
    }
}

PyObject* PyStr::__int__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    int x;
    try {
        istringstream in(this->toString());
        in.exceptions(ios_base::failbit | ios_base::badbit);
        in >> x;
        return new PyInt(x);
    } catch (...) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"invalid literal for int() with base 10: '"+this->toString()+"'");
    }
}

PyObject* PyStr::__bool__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    if (this->toString() == "")
        return new PyBool(false);

    return new PyBool(true);
}

PyObject* PyStr::__eq__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    PyStr* arg = (PyStr*) (*args)[0];
    
    if (this->toString() == arg->toString())
        return new PyBool(true);

    return new PyBool(false);
}

PyObject* PyStr::__funlist__(vector<PyObject*>* args) {
    int k;
    
    PyFunList* result = new PyFunList();
    
    for (k=val.size()-1;k>=0;k--) {
        ostringstream charstr;
        charstr << val[k];
        result = new PyFunList(new PyStr(charstr.str()), result);
    }
    
    return result;
}

PyType* PyStr::getType() {
    return PyTypes[PyStrType];
}

string PyStr::toString() {
    return val;
}

PyStr* PyStr::charAt(int index) {
    if (index >= val.size()) {
        throw new PyException(PYSTOPITERATIONEXCEPTION,"Stop Iteration");
    }
    
    ostringstream s;
    
    s  << val[index];
    //cerr <<"returning " << s << " from string iterator at index" << index << " size is " << val.size() << " val is " << val << endl;
    
    return new PyStr(s.str());
}

PyObject* PyStr::split(vector<PyObject*>* args) {
    string s = " \t\n";
    if (args->size() == 1) {
        PyStr* sepObj = (PyStr*) (*args)[0];
        s = sepObj->toString();
    }
    
    ostringstream os;
    
    os << s;
    
    string delim = os.str(); // convert escape chars
    
    vector<string> strs;
    
    ostringstream ss;
    
    for (int i=0;i<val.size();i++) {
        if (delim.find(val[i]) != string::npos) {
            strs.push_back(ss.str());
            ss.str("");
        } else {
            ss << val[i];
        }
    }
    
    strs.push_back(ss.str());
    
    vector<PyObject*>* strObjs = new vector<PyObject*>();
    
    for (int i=0; i<strs.size();i++) {
        strObjs->push_back(new PyStr(strs[i]));
    }
    
    return new PyList(strObjs);
}

PyObject* PyStr::__getitem__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyInt* intObj = (PyInt*) (*args)[0];
    
    int index = intObj->getVal();
    
    if (index >= val.size()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Index out of range");
    }
    
    ostringstream s;
    
    s  << val[index];
    
    return new PyStr(s.str());
}


PyObject* PyStr::__len__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyInt(val.size());
}

PyObject* PyStr::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyStrIterator(this);
}