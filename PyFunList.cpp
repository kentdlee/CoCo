/* 
 * File:   PyList.cpp
 * Author: kent
 * (c) 2013
 * Created on February 27, 2013, 9:12 PM
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

#include "PyFunList.h"
#include "PyFunListIterator.h"
#include "PyException.h"
#include "PyNone.h"
#include "PyInt.h"
#include "PyStack.h"
#include "PyStr.h"
#include <sstream>
using namespace std;

PyFunListElm::PyFunListElm(PyObject* head, PyFunListElm* tail) {
    this->head = head;
    this->tail = tail;
    if (tail!=NULL) {
        len = 1 + tail->len;
    } else {
        len = 1;
    }
}

PyFunListElm::~PyFunListElm() {
    try {
        delete head;
    } catch (...) {}
    try {
        delete tail;
    } catch (...) {}
}

string PyFunListElm::toString() {
    ostringstream s;
    
    s << head->toString();
    if (tail!=NULL) {
        s << ", " << tail->toString();
    }
    
    return s.str();
}

PyObject* PyFunListElm::getHead() {
    return head;
}

PyFunListElm* PyFunListElm::getTail() {
    return tail;
}

int PyFunListElm::getLen() {
    return len;
}

PyFunList::PyFunList(vector<PyObject*>* lst) : PyObject() {
    int k;
    PyFunListElm* tmp = NULL;
    for (k=lst->size()-1;k>=0;k--) {
        tmp = new PyFunListElm((*lst)[k],tmp);
    }
    data = tmp;
    
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__getitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__iter__);
    dict["__add__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__add__);
    dict["head"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::head);
    dict["tail"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::tail);
    dict["concat"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::concat);
}

PyFunList::PyFunList() : PyObject() {
    data = NULL;
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__getitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__iter__);
    dict["__add__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__add__);
    dict["head"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::head);
    dict["tail"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::tail);
    dict["concat"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::concat);  
}

PyFunList::PyFunList(PyObject* h, PyFunList* t) : PyObject() {
    data = new PyFunListElm(h,t->getElm());
    
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__getitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__iter__);
    dict["__add__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__add__);
    dict["head"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::head);
    dict["tail"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::tail);
    dict["concat"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::concat);
}

PyFunList::PyFunList(PyFunListElm* elm) : PyObject() {
    data = elm;
    
    dict["__getitem__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__getitem__);
    dict["__len__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__len__);
    dict["__iter__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__iter__);
    dict["__add__"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::__add__);
    dict["head"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::head);
    dict["tail"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::tail);
    dict["concat"] = (PyObject* (PyObject::*)(vector<PyObject*>*)) (&PyFunList::concat);
}

PyFunList::~PyFunList() {
}

PyType* PyFunList::getType() {
    return PyTypes[PyFunListType];
}

string PyFunList::toString() {
    ostringstream s;
    
    s << "[";
    
    if (data!=NULL)
       s << data->toString();
    
    s << "]";
    
    return s.str();
}

PyObject* PyFunList::__getitem__(vector<PyObject*>* args) {
    ostringstream msg; 
    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    if (data == NULL) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Attempt to index into an empty funlist.");    
    }
    
    PyInt* intObj = (PyInt*) (*args)[0];
    
    int index = intObj->getVal();
    
    if (index >= data->getLen()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Index out of range on funlist.");
    }
    
    PyFunListElm* tmp = data;
    
    for (int k=0;k<index;k++) {
        tmp = tmp->getTail();
    }
    
    return tmp->getHead();
}

PyObject* PyFunList::__len__(vector<PyObject*>* args) {
    ostringstream msg; 

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    if (data == NULL) {
        return new PyInt(0);
    }
    
    return new PyInt(data->getLen());
}

PyObject* PyFunList::__iter__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return new PyFunListIterator(this);
}

PyObject* PyFunList::__add__(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 1) {
        msg << "TypeError: expected 1 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    PyFunList* other = (PyFunList*)(*args)[0];
    PyStack<PyObject*> tmpStack;
    PyFunListElm* tmp = data;
    PyObject* val;
    
    while (tmp!=NULL) {
        tmpStack.push(tmp->getHead());
        tmp = tmp->getTail();
    }
    
    tmp = other->data;
    
    while (!tmpStack.isEmpty()) {
        val = tmpStack.pop();
        tmp = new PyFunListElm(val,tmp);
    }
    
    return new PyFunList(tmp);
}

PyFunListElm* PyFunList::getElm() {
    return data;
}

PyObject* PyFunList::getHead() {
    if (data == NULL) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Attempt to get head of empty funlist.");    
    }
    
    return getElm()->getHead();
}

PyFunList* PyFunList::getTail() {
    if (data == NULL) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION,"Attempt to get tail of empty funlist.");       
    }
    
    return new PyFunList(getElm()->getTail());
}

PyObject* PyFunList::head(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return getHead();
}

PyObject* PyFunList::tail(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    return getTail();
}

PyObject* PyFunList::concat(vector<PyObject*>* args) {
    ostringstream msg;

    if (args->size() != 0) {
        msg << "TypeError: expected 0 arguments, got " << args->size();
        throw new PyException(PYWRONGARGCOUNTEXCEPTION,msg.str());  
    }
    
    ostringstream s;
    
    PyFunListElm* tmp = data;
    
    while (data!=NULL) {
        s << data->getHead()->toString();
        data = data->getTail();
    }
    
    return new PyStr(s.str());
}
