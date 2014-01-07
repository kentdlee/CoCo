/* 
 * File:   PyListIterator.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 27, 2013, 9:36 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * PyListIterator objects provide the iterator interface by providing the 
 * __next__ magic method. The __iter__ is also provided because Python
 * implements the iter function by calling __iter__ on an iterator. Calling
 * iter on an iterator returns itself, as exhibited by the Python code below. 
 * Note that j must refer to the same value as i.
 * kent@kent-virtual-machine:~/NetBeansProjects/CoCo$ python3
 * Python 3.2.5 (default, Jul 22 2013, 10:45:32) 
 * [GCC 4.7.3] on linux2
 * Type "help", "copyright", "credits" or "license" for more information.
 * >>> x = "hi"
 * >>> i = iter(x)
 * >>> i.__next__()
 * 'h'
 * >>> j = iter(i)
 * >>> j.__next__()
 * 'i'
 * >>> i.__next__()
 * Traceback (most recent call last):
 *   File "<stdin>", line 1, in <module>
 * StopIteration
 * >>> j.__next__()
 * Traceback (most recent call last):
 *   File "<stdin>", line 1, in <module>
 * StopIteration
 * >>> 
 * 
 * From the shell interaction above you can see that StopIteration is an 
 * exception that is thrown to end the iteration. CoCo implements the end
 * of iteration in the same way. __next__ throws a StopIteration exception 
 * when there are no more elements to return. This exception is caught 
 * by the FOR_ITER instruction when it calls the __next__ method. The 
 * exception is handled by jumping to the loops exit point (i.e. the label
 * provided to the FOR_ITER instruction.  
 */

#ifndef PYLISTITERATOR_H
#define	PYLISTITERATOR_H

#include "PyObject.h"
#include "PyType.h"
#include "PyList.h"
#include <string>
using namespace std;

class PyListIterator : public PyObject {
public:
    PyListIterator(PyList* lst);
    virtual ~PyListIterator();
    
    PyType* getType();
    string toString();
    

protected:
    PyList* lst;
    int index;

    virtual PyObject* __iter__(vector<PyObject*>* args);
    virtual PyObject* __next__(vector<PyObject*>* args);    

};

#endif	/* PYLISTITERATOR_H */

