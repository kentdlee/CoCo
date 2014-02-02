/*
 * PyObject.h
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
 * And here is where it all began. Now, while I haven't studied the 
 * the implementation of Python in C, it is pretty clear that PyObjects 
 * are a dictionary mapping magic method names to function pointers that
 * point to the C code of their respective implementations. 
 * 
 * In CoCo I made the decision to use C++ as much as possible and to use
 * C++ inheritance to implement the magic methods. So, all magic methods
 * are declared as virtual functions. Either PyObject or subclasses of 
 * this class can implement these methods, either all or some, in whatever
 * way they see fit. I found the list of magic methods on the web at 
 * http://www.rafekettler.com/magicmethods.html. As I developed CoCo and
 * added support for a few more datatypes, there were two more magic methods
 * that I found useful to implement. The "type" function calls the __type__
 * magic method. The __excmatch__ magic method is called when comparing 
 * an exception to a match in an exception handler. 
 * 
 * Finally, there are a few methods that are classified as methods on
 * objects in Python, like the split method on strings. These methods 
 * are defined where appropriate.
 * 
 * The entire list of magic methods is included in this header file below, but
 * not all of them are implemented in this class or in subclasses. They are
 * provided here as a reference only to all the methods that could be defined.
 */

#ifndef PYOBJECT_H_
#define PYOBJECT_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

class PyType; 

class PyObject {
public:
	PyObject();
	virtual ~PyObject();
	virtual PyType* getType();
   virtual string toString();
   void decRef();
   void incRef();
   int getRefCount() const;
        
   PyObject* callMethod(string name, vector<PyObject*>* args);
       
protected:
    unordered_map<string, PyObject* (PyObject::*)(vector<PyObject*>*)> dict;        
    int refCount;
    
    virtual PyObject* __str__(vector<PyObject*>* args);
    virtual PyObject* __type__(vector<PyObject*>* args);     
};

ostream& operator << (ostream& os, PyObject& t);

extern bool verbose;

/* This list of methods came from 
 *      http://www.rafekettler.com/magicmethods.html

   virtual PyObject* __cmp__(vector<PyObject*>* args);
   virtual PyObject* __eq__(vector<PyObject*>* args);
   virtual PyObject* __ne__(vector<PyObject*>* args);
   virtual PyObject* __lt__(vector<PyObject*>* args);
   virtual PyObject* __gt__(vector<PyObject*>* args);
   virtual PyObject* __le__(vector<PyObject*>* args);
   virtual PyObject* __ge__(vector<PyObject*>* args);
   virtual PyObject* __pos__(vector<PyObject*>* args);
   virtual PyObject* __neg__(vector<PyObject*>* args);
   virtual PyObject* __abs__(vector<PyObject*>* args);
   virtual PyObject* __invert__(vector<PyObject*>* args);
   virtual PyObject* __round__(vector<PyObject*>* args);
   virtual PyObject* __floor__(vector<PyObject*>* args);
   virtual PyObject* __ceil__(vector<PyObject*>* args);
   virtual PyObject* __trunc__(vector<PyObject*>* args);
   virtual PyObject* __add__(vector<PyObject*>* args);
   virtual PyObject* __sub__(vector<PyObject*>* args);
   virtual PyObject* __mul__(vector<PyObject*>* args);
   virtual PyObject* __floordiv__(vector<PyObject*>* args);
   virtual PyObject* __div__(vector<PyObject*>* args);
   virtual PyObject* __truediv__(vector<PyObject*>* args);
   virtual PyObject* __mod__(vector<PyObject*>* args);
   virtual PyObject* __divmod__(vector<PyObject*>* args);
   virtual PyObject* __pow__(vector<PyObject*>* args);
   virtual PyObject* __lshift__(vector<PyObject*>* args);
   virtual PyObject* __rshift__(vector<PyObject*>* args);
   virtual PyObject* __and__(vector<PyObject*>* args);
   virtual PyObject* __or__(vector<PyObject*>* args);
   virtual PyObject* __xor__(vector<PyObject*>* args);
   virtual PyObject* __radd__(vector<PyObject*>* args);
   virtual PyObject* __rsub__(vector<PyObject*>* args);
   virtual PyObject* __rmul__(vector<PyObject*>* args);
   virtual PyObject* __rfloordiv__(vector<PyObject*>* args);
   virtual PyObject* __rdiv__(vector<PyObject*>* args);
   virtual PyObject* __rtruediv__(vector<PyObject*>* args);
   virtual PyObject* __rmod__(vector<PyObject*>* args);
   virtual PyObject* __rdivmod__(vector<PyObject*>* args);
   virtual PyObject* __rpow__(vector<PyObject*>* args);
   virtual PyObject* __rlshift__(vector<PyObject*>* args);
   virtual PyObject* __rrshift__(vector<PyObject*>* args);
   virtual PyObject* __rand__(vector<PyObject*>* args);
   virtual PyObject* __ror__(vector<PyObject*>* args);
   virtual PyObject* __rxor__(vector<PyObject*>* args);
   virtual PyObject* __iadd__(vector<PyObject*>* args);
   virtual PyObject* __isub__(vector<PyObject*>* args);
   virtual PyObject* __imul__(vector<PyObject*>* args);
   virtual PyObject* __ifloordiv__(vector<PyObject*>* args);
   virtual PyObject* __idiv__(vector<PyObject*>* args);
   virtual PyObject* __itruediv__(vector<PyObject*>* args);
   virtual PyObject* __imod__(vector<PyObject*>* args);
   virtual PyObject* __ipow__(vector<PyObject*>* args);
   virtual PyObject* __ilshift__(vector<PyObject*>* args);
   virtual PyObject* __iand__(vector<PyObject*>* args);
   virtual PyObject* __ior__(vector<PyObject*>* args);
   virtual PyObject* __ixor__(vector<PyObject*>* args);
   virtual PyObject* __int__(vector<PyObject*>* args);
   virtual PyObject* __long__(vector<PyObject*>* args);
   virtual PyObject* __float__(vector<PyObject*>* args);
   virtual PyObject* __bool__(vector<PyObject*>* args);
   // editor didn't like __complex__, or was it C++?
   virtual PyObject* __cmplex__(vector<PyObject*>* args); 
   virtual PyObject* __oct__(vector<PyObject*>* args);
   virtual PyObject* __hex__(vector<PyObject*>* args);
   virtual PyObject* __index__(vector<PyObject*>* args);
   virtual PyObject* __coerce__(vector<PyObject*>* args);
   virtual PyObject* __str__(vector<PyObject*>* args);
   virtual PyObject* __list__(vector<PyObject*>* args);
   virtual PyObject* __funlist__(vector<PyObject*>* args);
   virtual PyObject* __repr__(vector<PyObject*>* args);
   virtual PyObject* __unicode__(vector<PyObject*>* args);
   virtual PyObject* __format__(vector<PyObject*>* args);
   virtual PyObject* __hash__(vector<PyObject*>* args);
   virtual PyObject* __nonzero__(vector<PyObject*>* args);
   virtual PyObject* __dir__(vector<PyObject*>* args);
   virtual PyObject* __sizeof__(vector<PyObject*>* args);
   virtual PyObject* __getattr__(vector<PyObject*>* args);
   virtual PyObject* __setattr__(vector<PyObject*>* args);
   virtual PyObject* __delattr__(vector<PyObject*>* args);
   virtual PyObject* __getattribute__(vector<PyObject*>* args);
   virtual PyObject* __len__(vector<PyObject*>* args);
   virtual PyObject* __getitem__(vector<PyObject*>* args);
   virtual PyObject* __setitem__(vector<PyObject*>* args);
   virtual PyObject* __delitem__(vector<PyObject*>* args);
   virtual PyObject* __reversed__(vector<PyObject*>* args);
   virtual PyObject* __contains__(vector<PyObject*>* args);
   virtual PyObject* __missing__(vector<PyObject*>* args);
   virtual PyObject* __instancecheck__(vector<PyObject*>* args);
   virtual PyObject* __subclasscheck__(vector<PyObject*>* args);
   virtual PyObject* __call__(vector<PyObject*>* args);
   virtual PyObject* __copy__(vector<PyObject*>* args);
   virtual PyObject* __deepcopy__(vector<PyObject*>* args); 
   virtual PyObject* __iter__(vector<PyObject*>* args);
   virtual PyObject* __next__(vector<PyObject*>* args);


   //These I added for my implementation.
   virtual PyObject* __type__(vector<PyObject*>* args); 
   virtual PyObject* __excmatch__(vector<PyObject*>* args);


   //These are methods (attributes called Attr in Python) 
   //that might be defined on subclasses.
   virtual PyObject* split(vector<PyObject*>* args); 
   virtual PyObject* append(vector<PyObject*>* args);
   virtual PyObject* head(vector<PyObject*>* args);
   virtual PyObject* tail(vector<PyObject*>* args);
   virtual PyObject* concat(vector<PyObject*>* args);
*/

#endif /* PYOBJECT_H_ */
