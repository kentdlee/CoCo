/* 
 * File:   PyParser.cpp
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
 * The format of programs for the CoCo virtual machine is given by the following
 * grammar. This grammar is LL(1) and therefore can be implemented as a top
 * down parser. The methods of the PyParser class implement this top-down 
 * parser. Each non-terminal of the grammar below becomes a function in the 
 * top-down parser. Non-terminals that appear on the rhs (right-hand side) of a 
 * rule correspond to function calls. Tokens that appear on the rhs of a rule 
 * can be retrieved from the scanner by calling getToken on the scanner. Because
 * the grammar is LL(1), once in a while a token must be read to look ahead (needed
 * in deciding which rule to apply in some cases). In those cases, the token may
 * be put back using the putBackToken method. Only one token may be put back
 * on the scanner. Calling putBackToken multiple times will only put the last token
 * back once (until it is retrieved with getToken again). 
 * 
 * Here is the grammar.
 * ===========================================================================
 * PyAssemblyProg ::= FunctionListPart EOF
 * FunctionListPart ::= FunDef FunctionList
 * FunctionList ::= FunDef FunctionList | <null>
 * FunDef ::= Function colon Identifier slash Integer FunctionList ConstPart LocalsPart 
 *               FreeVarsPart CellVarsPart GlobalsPart BodyPart
 * ConstPart ::= <null> | Constants colon ValueList
 * ValueList ::= Value ValueRest
 * ValueRest ::= comma ValueList | <null>
 * Value ::= None | Integer | Float | String   (* the Scanner recognizes None as an Identifier *)
 * LocalsPart ::= <null> | Locals colon IdList
 * FeeVarsPart ::= <null> | FreeVars colon IdList
 * CellVarsPart ::= <null> | CellVars colon IdList
 * IdList ::= Identifier IdRest
 * IdRest ::= comma IdList | <null>
 * GlobalsPart ::= <null> | Globals colon IdList
 * BodyPart ::= BEGIN InstructionList END
 * InstructionList ::= <null> | LabeledInstruction InstructionList
 * LabeledInstruction ::= Identifier colon LabeledInstruction | Instruction | OpInstruction
 * Instruction ::= STOP_CODE | NOP | POP_TOP | ROT_TWO | ROT_THREE | ...
 * OpInstruction ::= OpMnemonic Integer | OpMnemonic Identifier
 * OpMnemonic ::= LOAD_CONST | STORE_FAST | SETUP_LOOP | COMPARE_OP | POP_JUMP_IF_FALSE | ...
 * ============================================================================
 * The implementation below cheats a little bit and combines the LabeledInstruction,
 * UnaryInstruction, BinaryInstruction, and BinaryMneomic non-terminals into
 * one function (the LabeledInstruction function). 
 * 
 */

#include "PyParser.h"
#include "PyObject.h"
#include "PyException.h"
#include "PyInt.h"
#include "PyFloat.h"
#include "PyStr.h"
#include "PyBool.h"
#include "PyNone.h"
#include "PyUtil.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

void badToken(PyToken* tok, string message) {
    cerr << "*********************************************************" << endl;
    cerr << "              A Parse Exception Occurred" << endl;
    cerr << "*********************************************************" << endl;
    cerr << "Bad token '" << tok->getLex() << "' found at line " << tok->getLine() << " and column " << tok->getCol() << "." << endl;
    cerr << "Token type was " << tok->getType() << "." << endl;
    cerr << message << endl;
    exit(0);
}

vector<PyCode*>* PyParser::parse() {
    try {
        return PyAssemblyProg();
    } catch (PyException* ex) {
        in->putBackToken();
        PyToken* tok = in->getToken();
        cerr << "*********************************************************" << endl;
        cerr << "              A Parse Exception Occurred" << endl;
        cerr << "*********************************************************" << endl;
        cerr << "The exception occurred at line " << tok->getLine() << " and column " << tok->getCol() << "." << endl;
        cerr << "The exception was: " << ex->toString() << endl;
        exit(0);
    }
}

PyParser::PyParser(string filename) {
    istream* stream = new ifstream(filename);
    this->in = new PyScanner(stream);

}

PyParser::PyParser(const PyParser& orig) {
    this->in = orig.in;
}

PyParser::~PyParser() {
    try {
        delete in;
    } catch (...) {
    }
}

vector<PyCode*>* PyParser::PyAssemblyProg() {

    vector<PyCode*>* code = FunctionListPart();

    PyToken* tok = in->getToken();

    if (tok->getType() != PYEOFTOKEN)
        badToken(tok, "Expected End Of File marker.");

    return code;

}

vector<PyCode*>* PyParser::FunctionListPart() {
    PyCode* code = FunDef();

    vector<PyCode*>* vec = new vector<PyCode*>();

    vec->push_back(code);

    vec = FunctionList(vec);

    return vec;
}

vector<PyCode*>* PyParser::FunctionList(vector<PyCode*>* vec) {
    PyToken* tok = in->getToken();
    in->putBackToken();

    if (tok->getLex() == "Function") {

        PyCode* code = FunDef();

        vec->push_back(code);

        vec = FunctionList(vec);
    }

    return vec;
}

PyCode* PyParser::FunDef() {
    PyToken* tok = in->getToken();

    if (tok->getLex() != "Function")
        badToken(tok, "Expected Function keyword.");

    tok = in->getToken();

    if (tok->getLex() != ":")
        badToken(tok, "Expected a colon.");

    PyToken* funName = in->getToken();

    if (funName->getType() != PYIDENTIFIERTOKEN)
        badToken(funName, "Expected an identifier.");

    tok = in->getToken();

    if (tok->getLex() != "/")
        badToken(tok, "Expected a '/'.");

    PyToken* numArgsToken = in->getToken();
    int numArgs;

    if (numArgsToken->getType() != PYINTEGERTOKEN)
        badToken(numArgsToken, "Expected an integer for the argument count.");

    istringstream numArgsIn(numArgsToken->getLex(), istringstream::in);
    numArgsIn.exceptions(ios_base::failbit | ios_base::badbit);
    numArgsIn >> numArgs;

    vector<PyCode*>* nestedFunctions = new vector<PyCode*>();

    nestedFunctions = FunctionList(nestedFunctions);

    vector<PyObject*>* constants = ConstPart(nestedFunctions);

    vector<string>* locals = LocalsPart();

    vector<string>* freevars = FreeVarsPart();

    vector<string>* cellvars = CellVarsPart();

    vector<string>* globals = GlobalsPart();

    vector<PyByteCode*>* instructions = BodyPart();

    return new PyCode(funName->getLex(), nestedFunctions, constants, locals, freevars, cellvars, globals, instructions, numArgs);
}

vector<PyObject*>* PyParser::ConstPart(vector<PyCode*>* nestedFunctions) {
    vector<PyObject*>* constants = new vector<PyObject*>();

    PyToken* tok = in->getToken();

    if (tok->getLex() != "Constants") {
        in->putBackToken();
        return constants;
    }

    tok = in->getToken();

    if (tok->getLex() != ":")
        badToken(tok, "Expected a ':'.");

    constants = ValueList(constants, nestedFunctions);

    return constants;
}

vector<PyObject*>* PyParser::ValueList(vector<PyObject*>* constants, vector<PyCode*>* nestedFunctions) {
    PyObject* value = Value(nestedFunctions);
    constants->push_back(value);
    constants = ValueRest(constants, nestedFunctions);
    return constants;
}

vector<PyObject*>* PyParser::ValueRest(vector<PyObject*>* constants, vector<PyCode*>* nestedFunctions) {
    PyToken* tok = in->getToken();

    if (tok->getLex() != ",") {
        in->putBackToken();
        return constants;
    }

    return ValueList(constants, nestedFunctions);
}

PyObject* PyParser::Value(vector<PyCode*>* nestedFunctions) {
    int iVal;
    float fVal;
    string sVal;
    PyToken* codeId;
    istringstream* tokStr;

    PyToken* tok = in->getToken();

    switch (tok->getType()) {
        case PYINTEGERTOKEN:
            tokStr = new istringstream(tok->getLex());
            tokStr->exceptions(ios_base::failbit | ios_base::badbit);
            (*tokStr) >> iVal;
            delete tokStr;
            return new PyInt(iVal);
            break;
        case PYFLOATTOKEN:
            tokStr = new istringstream(tok->getLex());
            tokStr->exceptions(ios_base::failbit | ios_base::badbit);
            (*tokStr) >> fVal;
            delete tokStr;
            return new PyFloat(fVal);
            break;
        case PYSTRINGTOKEN:
            sVal = tok->getLex();
            return new PyStr(sVal);
            break;
        case PYIDENTIFIERTOKEN:
            if (tok->getLex() == "None")
                return new PyNone();
            else if (tok->getLex() == "True")
                return new PyBool(true);
            else if (tok->getLex() == "False")
                return new PyBool();
            else if (tok->getLex() == "code") {
                tok = in->getToken();

                if (tok->getLex() != "(")
                    badToken(tok, "Expected a '('.");

                codeId = in->getToken();

                if (codeId->getType() != PYIDENTIFIERTOKEN)
                    badToken(tok, "Expected an identifier.");

                tok = in->getToken();

                if (tok->getLex() != ")")
                    badToken(tok, "Expected a ')'.");

                for (int i = 0; i < nestedFunctions->size(); i++) {
                    PyCode* code = (*nestedFunctions)[i];
                    if (code->getName() == codeId->getLex()) {
                        return code;
                    }
                }

                cerr << "Identifier " << codeId->getLex() << " is not a nested function." << endl;
                badToken(codeId, "Must be name of inner function.");
            } else
                badToken(tok, "Expected None, int, float, str, True, or False.");
        default:
            badToken(tok, "Expected None, int, float, str, True, or False.");
            break;
    }

    return NULL; // This won't happen, but C++ OS X compiler warns without. 
}

vector<string>* PyParser::LocalsPart() {
    vector<string>* locals = new vector<string > ();

    PyToken* tok = in->getToken();

    if (tok->getLex() != "Locals") {
        in->putBackToken();
        return locals;
    }

    tok = in->getToken();

    if (tok->getLex() != ":")
        badToken(tok, "Expected a ':'.");

    return IdList(locals);
}

vector<string>* PyParser::FreeVarsPart() {
    vector<string>* freevars = new vector<string > ();

    PyToken* tok = in->getToken();

    if (tok->getLex() != "FreeVars") {
        in->putBackToken();
        return freevars;
    }

    tok = in->getToken();

    if (tok->getLex() != ":")
        badToken(tok, "Expected a ':'.");

    return IdList(freevars);
}

vector<string>* PyParser::CellVarsPart() {
    vector<string>* cellvars = new vector<string > ();

    PyToken* tok = in->getToken();

    if (tok->getLex() != "CellVars") {
        in->putBackToken();
        return cellvars;
    }

    tok = in->getToken();

    if (tok->getLex() != ":")
        badToken(tok, "Expected a ':'.");

    return IdList(cellvars);
}

vector<string>* PyParser::IdList(vector<string>* lst) {
    PyToken* tok = in->getToken();

    if (tok->getType() != PYIDENTIFIERTOKEN)
        badToken(tok, "Expected an identifier.");

    lst->push_back(tok->getLex());

    return IdRest(lst);
}

vector<string>* PyParser::IdRest(vector<string>* lst) {
    PyToken* tok = in->getToken();

    if (tok->getType() != PYCOMMATOKEN) {
        in->putBackToken();
        return lst;
    }

    return IdList(lst);
}

vector<string>* PyParser::GlobalsPart() {
    vector<string>* globals = new vector<string>();

    PyToken* tok = in->getToken();

    if (tok->getLex() != "Globals") {
        in->putBackToken();
        return globals;
    }

    tok = in->getToken();

    if (tok->getLex() != ":")
        badToken(tok, "Expected a ':'.");

    return IdList(globals);
}

vector<PyByteCode*>* PyParser::BodyPart() {
    vector<PyByteCode*>* instructions = new vector<PyByteCode*> ();

    PyToken* tok = in->getToken();

    target.clear();
    index = 0;

    if (tok->getLex() != "BEGIN")
        badToken(tok, "Expected a BEGIN keyword.");

    instructions = InstructionList(instructions);

    //Find the target of any labels in the byte code instructions
    int i;

    for (i = 0; i < instructions->size(); i++) {
        PyByteCode* inst = (*instructions)[i];
        string label = inst->getLabel();

        if (label != "") {
            string op = inst->getOpCodeName();
            delete (*instructions)[i];
            (*instructions)[i] = new PyByteCode(op, target[label]);
        }
    }

    tok = in->getToken();

    if (tok->getLex() != "END")
        badToken(tok, "Expected a END keyword.");

    //printMap<string,int>(target);

    return instructions;
}

vector<PyByteCode*>* PyParser::InstructionList(vector<PyByteCode*>* instructions) {
    PyToken* tok = in->getToken();
    in->putBackToken();

    if (tok->getLex() == "END")
        return instructions;


    PyByteCode* inst = LabeledInstruction();

    instructions->push_back(inst);
    index++;

    return InstructionList(instructions);
}

PyByteCode* PyParser::LabeledInstruction() {
    PyToken* tok1 = in->getToken();
    string tok1Lex = tok1->getLex();

    PyToken* tok2 = in->getToken();
    string tok2Lex = tok2->getLex();

    if (tok2Lex == ":") {
        if (target.find(tok1Lex) == target.end()) {
            target[tok1Lex] = index;
        } else
            badToken(tok1, "Duplicate label found.");

        return LabeledInstruction();
    }

    int argCount = 0;

    try {
        argCount = PyByteCode::numArgs(tok1Lex);
    } catch (int e) {
        badToken(tok1, "Illegal Opcode.");
    }

    if (argCount == 0) {
        in->putBackToken();
        return new PyByteCode(tok1Lex);
    }

    if (tok2->getType() == PYIDENTIFIERTOKEN) {
        // found a label to jump to.
        try {
            return new PyByteCode(tok1Lex, tok2Lex);
        } catch (int e) {
            badToken(tok2, "Illegal Opcode.");
        }
    }

    if (tok2->getType() == PYINTEGERTOKEN) {
        try {
            int operand;
            stringstream(tok2Lex) >> operand;
            return new PyByteCode(tok1Lex, operand);

        } catch (int e) {
            badToken(tok1, "Illegal Opcode.");
        }
    }

    badToken(tok1, "Instruction Syntax Error.");

    return NULL; // This won't happen but C++ OS X compiler warns without. 
}

