/* 
 * File:   PyTupleIterator.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on March 7, 2013, 11:37 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * The class that implements iteration over a tuple. As with other iterators,
 * calling the __iter__ magic method on an string iterator as shown below has 
 * no effect other than to return an alias to itself. See the PyStrIterator.h
 * file for a further discussion of how iterators work.
 */

#ifndef PYTUPLEITERATOR_H
#define	PYTUPLEITERATOR_H

#include "PyObject.h"
#include "PyType.h"
#include "PyTuple.h"
#include <string>
using namespace std;

class PyTupleIterator : public PyObject {
public:
    PyTupleIterator(PyTuple* lst);
    virtual ~PyTupleIterator();  
    PyType* getType();
    string toString();
    
protected:
    PyTuple* lst;
    int index;
    
    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __next__(vector<PyObject*>* args);
};


#endif	/* PYTUPLEITERATOR_H */

