/* 
 * File:   PyNone.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 14, 2013, 7:24 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * This is the special value None that is returned by all functions if they
 * do not explicitly return a value. It is also the special value used as a 
 * null reference. 
 * 
 */

#ifndef PYNONE_H
#define	PYNONE_H

#include "PyObject.h"

class PyNone : public PyObject {
public:
    PyNone();
    PyNone(const PyNone& orig);
    virtual ~PyNone();
    PyType* getType();
    string toString();
    
protected:

};

#endif	/* PYNONE_H */

