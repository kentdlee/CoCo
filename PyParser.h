/* 
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 11, 2013, 10:38 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * The PyParser object parses the input file and produces an abstract syntax
 * tree representing the program. In CoCo, the abstract syntax tree is 
 * represented as a vector of PyCode pointers. Each PyCode object represents
 * one function from the assembly language input file. The parser is 
 * implemented as a recursive descent parser. See PyParser.cpp for the BNF
 * of the grammar. 
 */

#ifndef PYPARSER_H
#define	PYPARSER_H
#include "PyScanner.h"
#include "PyCode.h"
#include "PyObject.h"
#include <vector>
#include <unordered_map>
using namespace std;


class PyParser {
public:
    PyParser(string filename);
    PyParser(const PyParser& orig);
    virtual ~PyParser();
    vector<PyCode*>* parse();
private:
    PyScanner* in;
    
    // These two fields are used when determining the addresses of 
    // labels within the code that is generated for jump instructions.
    unordered_map<string,int> target;
    int index;
    
    vector<PyCode*>* PyAssemblyProg();
    vector<PyCode*>* FunctionListPart();
    vector<PyCode*>* FunctionList(vector<PyCode*>* vec);

    PyCode* FunDef();
    vector<PyObject*>* ConstPart(vector<PyCode*>* nestedFuns);
    vector<PyObject*>* ValueList(vector<PyObject*>* constants, vector<PyCode*>* nestedFunctions);
    vector<PyObject*>* ValueRest(vector<PyObject*>* constants, vector<PyCode*>* nestedFunctions);
    PyObject* Value(vector<PyCode*>* nestedFunctions);
    vector<string>* LocalsPart();
    vector<string>* FreeVarsPart();
    vector<string>* CellVarsPart();
    vector<string>* IdList(vector<string>* lst);
    vector<string>* IdRest(vector<string>* lst);
    vector<string>* GlobalsPart();
    vector<PyByteCode*>* BodyPart();
    vector<PyByteCode*>* InstructionList(vector<PyByteCode*>*);
    PyByteCode* LabeledInstruction();

};

#endif	/* PYPARSER_H */

