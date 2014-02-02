/*
 * PyException.h
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
 * PyExceptions are thrown for error conditions and when raised by source
 * programs in CoCo. An exception contains a constant indicating the type 
 * of the exception and either a message string or a Python object. If a 
 * message string is passed, it is stored in the exception as a PyStr object.
 * 
 * The exception types are listed below the class declaration. 
 * 
 * When an exception is raised in CoCo a real C++ exception is also raised.
 * There can be one of two outcomes. The CoCo may intend to catch or 
 * handle the exception. If that is the case, an exception handler will have
 * been installed via the SETUP_EXCEPT instruction. This pushes an exception
 * block onto the block stack. 
 * 
 * Any exception is first caught by the virtual machine in its fetch/execute
 * loop in PyFrame. If an exception handler block is found on the block stack,
 * then control is passed to the exception handler (the PC is set to the 
 * handler). 
 * 
 * If no exception handling block is found, the current PyFrame object is 
 * added to the traceback of this exception. The traceback is a vector of 
 * PyFrame pointers. Each PyFrame corresponds to one function call. The 
 * traceback forms a copy of the run-time stack at the time the exception 
 * first occurred back to where it was caught. If no exception handler, in 
 * any activation record, catches the exception, then the main code prints
 * the traceback along with exception information so the user can see where
 * the exception occurred. 
 * 
 * The exception constants below define the different types of reported
 * exceptions. The PYSTOPITERATIONEXCEPTION is used to end iteration (see
 * the PyListIterator.h description for more detail. 
 * 
 * The __excmatch__ magic method below is implemented to check the argument
 * passed to it against the type of the current object's exception. This
 * is needed when an except block is catching a particular type of exception. 
 */

#ifndef PYEXCEPTION_H_
#define PYEXCEPTION_H_

#include "PyObject.h"
class PyFrame;
#include <string>
using namespace std;

class PyException : public PyObject {
public:
    PyException(int exceptType, PyObject* val);
    PyException(int exceptType, string message);
    virtual ~PyException();
    int getExceptionType();
    void tracebackAppend(PyFrame* frame);
    string toString();
    PyType* getType();
    PyObject* getTraceBack();
    void printTraceBack();


protected:
    /* This is only here for debugging purposes. The exception type should be
     * the second field within the object if the first field indicates an exception.
     */
    int exceptionType;
    PyObject* val;
    vector<PyFrame*> traceback;

    virtual PyObject* __excmatch__(vector<PyObject*>* args);
};

const int PYEXCEPTION = 1;
const int PYEMPTYSTACKEXCEPTION = 2;
const int PYPARSEEXCEPTION = 3;
const int PYILLEGALOPERATIONEXCEPTION = 4;
const int PYWRONGARGCOUNTEXCEPTION = 5;
const int PYSTOPITERATIONEXCEPTION = 6;
const int PYMATCHEXCEPTION = 7;

#endif /* PYEXCEPTION_H_ */
