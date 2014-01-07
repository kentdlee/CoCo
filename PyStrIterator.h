/* 
 * File:   PyStrIterator.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 28, 2013, 9:55 AM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * Iteration over a string is provided by this class. As with other iterators,
 * calling the __iter__ magic method on an string iterator as shown below has 
 * no effect other than to return an alias to itself. 
 * Python 3.2.5 (default, Jul 22 2013, 10:45:32) 
 * [GCC 4.7.3] on linux2
 * Type "help", "copyright", "credits" or "license" for more information.
 * >>> s = "hello"
 * >>> i = iter(s)
 * >>> i.__next__()
 * 'h'
 * >>> j = iter(i)
 * >>> j.__next__()
 * 'e'
 * >>> i.__next__()
 * 'l'
 * >>>
 * 
 * When the iterator is exhausted, the __next__ magic method raises the 
 * PYSTOPITERATION exception. This is handled by the FOR_ITER instruction 
 * to end the iteration. 
 */

#ifndef PYSTRITERATOR_H
#define	PYSTRITERATOR_H

#include "PyObject.h"
#include "PyType.h"
#include "PyStr.h"

class PyStrIterator : public PyObject {
public:
    PyStrIterator(PyStr* str);
    virtual ~PyStrIterator();
    
    PyType* getType();
    string toString();
    


private:
    PyStr* str;
    int index;

    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __next__(vector<PyObject*>* args);
};

#endif	/* PYSTRITERATOR_H */

