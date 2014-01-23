/*
 * PyStack.h
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
 * Here we have an example of a template. This template is used 
 * for both the operand stack (in PyFrame) and the block stack. 
 * Templates in C++ are like generic classes in Java. The code 
 * is written generically so that a stack is a stack of some other 
 * type of element. The __PyStackElement defines a linked list of
 * the elements to be put on the stack. The toString method can 
 * be used in debugging to see the contents of a stack. 
 * 
 * Since we really don't know the type of T, we cannot delete the 
 * elements that are pushed on the stack when deleting a stack. 
 * This is a potential memory leak. It might be safer to throw an 
 * exception if a non-empty stack is deleted. However, if we have
 * stack of ints, then the ints would not have to be deleted. So 
 * this is left up to the programmer to know what they are doing. 
 * If the stack is a stack of pointers to dynamically allocated 
 * objects, the stack should be emptied before it is deleted.
 * Otherwise, if T is anything else then explicitly deleting the 
 * T elements is not necessary and is implicitly handled in 
 * this implementation (when deleting the __PyStackElements). 
 */

#ifndef PYSTACK_H_
#define PYSTACK_H_

#include "PyException.h"
#include <sstream>

template<class T>
class __PyStackElement {
public:
	__PyStackElement(T element);
    virtual ~__PyStackElement();

	T object;
	__PyStackElement<T>* next;

};

template<class T>
class PyStack {
public:
	PyStack();
	virtual ~PyStack();
	T pop();
	void push(T object);
	T top();
	bool isEmpty();
    string toString();
    int getCount();

private:
	__PyStackElement<T>* tos;
    int count;
};


template <class T>
PyStack<T>::PyStack() {
	tos = NULL;
}

template <class T>
PyStack<T>::~PyStack() {
	if (tos != NULL) {
		try {
			delete tos;
		} catch (...) {}
	}
}

template <class T>
string PyStack<T>::toString() {
    stringstream out;
    
    out << "top" << endl;
    
    __PyStackElement<T>* cursor;
    
    cursor = tos;
    
    while (cursor!=NULL) {
        out << *(cursor->object) << endl;
        cursor = cursor->next;
    }
    
    return out.str();
}

template <class T>
int PyStack<T>::getCount() {
    return this->count;
}

template <class T>
T PyStack<T>::pop() {
	if (tos != NULL) {
		__PyStackElement<T>* elem = tos;
		T val = elem->object;
		tos = tos->next;
        // The following line is needed to be able 
        // to delete elem without deleting the rest
        // of the stack. 
        elem->next = NULL; 
		delete elem;
        count --;
		return val;
	}

	throw new PyException(PYEMPTYSTACKEXCEPTION, "Attempt to pop an empty stack");     
}

template <class T>
void PyStack<T>::push(T object) {
	__PyStackElement<T>* elem = new __PyStackElement<T>(object);
	elem->next = tos;
	tos = elem;
    count++;
}

template <class T>
T PyStack<T>::top() {
	if (tos!=NULL) {
		T val = tos->object;
		return val;
	}

	throw new PyException(PYEMPTYSTACKEXCEPTION, "Attempt to get top of empty stack.");
        
}

template <class T>
bool PyStack<T>::isEmpty() {
	return (tos == NULL);
}

template <class T>
__PyStackElement<T>::__PyStackElement(T obj) {
	object = obj;
	next = NULL;
}

template <class T>
__PyStackElement<T>::~__PyStackElement() {
    if (next != NULL) {
		try {
			delete next;
		} catch (...) {}
	}
}

#endif /* PYSTACK_H_ */
