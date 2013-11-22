/* 
 * File:   PyCallable.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 17, 2013, 12:21 AM
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
 */

#include "PyCallable.h"

PyCallable::PyCallable() {
}

PyCallable::PyCallable(const PyCallable& orig) {
}

PyCallable::~PyCallable() {
}

bool PyCallable::isCallable() const {
    return true;
}
