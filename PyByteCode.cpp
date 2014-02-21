/* File:   PyByteCode.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 11, 2013, 11:26 AM
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
 * 
 */

#include "PyByteCode.h"
#include "PyException.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

bool create_map(unordered_map<string, PyOpCode>& m) {
    m["STOP_CODE"] = STOP_CODE;
    m["NOP"] = NOP;
    m["POP_TOP"] = POP_TOP;
    m["ROT_TWO"] = ROT_TWO;
    m["ROT_THREE"] = ROT_THREE;
    m["DUP_TOP"] = DUP_TOP;
    m["DUP_TOP_TWO"] = DUP_TOP_TWO;
    m["UNARY_POSITIVE"] = UNARY_POSITIVE;
    m["UNARY_NEGATIVE"] = UNARY_NEGATIVE;
    m["UNARY_NOT"] = UNARY_NOT;
    m["UNARY_INVERT"] = UNARY_INVERT;
    m["GET_ITER"] = GET_ITER;
    m["BINARY_POWER"] = BINARY_POWER;
    m["BINARY_MULTIPLY"] = BINARY_MULTIPLY;
    m["BINARY_FLOOR_DIVIDE"] = BINARY_FLOOR_DIVIDE;
    m["BINARY_TRUE_DIVIDE"] = BINARY_TRUE_DIVIDE;
    m["BINARY_MODULO"] = BINARY_MODULO;
    m["BINARY_ADD"] = BINARY_ADD;
    m["BINARY_SUBTRACT"] = BINARY_SUBTRACT;
    m["BINARY_SUBSCR"] = BINARY_SUBSCR;
    m["BINARY_LSHIFT"] = BINARY_LSHIFT;
    m["BINARY_RSHIFT"] = BINARY_RSHIFT;
    m["BINARY_AND"] = BINARY_AND;
    m["BINARY_XOR"] = BINARY_XOR;
    m["BINARY_OR"] = BINARY_OR;
    m["INPLACE_POWER"] = INPLACE_POWER;
    m["INPLACE_MULTIPLY"] = INPLACE_MULTIPLY;
    m["INPLACE_FLOOR_DIVIDE"] = INPLACE_FLOOR_DIVIDE;
    m["INPLACE_TRUE_DIVIDE"] = INPLACE_TRUE_DIVIDE;
    m["INPLACE_MODULO"] = INPLACE_MODULO;
    m["INPLACE_ADD"] = INPLACE_ADD;
    m["INPLACE_SUBTRACT"] = INPLACE_SUBTRACT;
    m["INPLACE_LSHIFT"] = INPLACE_LSHIFT;
    m["INPLACE_RSHIFT"] = INPLACE_RSHIFT;
    m["INPLACE_AND"] = INPLACE_AND;
    m["INPLACE_XOR"] = INPLACE_XOR;
    m["INPLACE_OR"] = INPLACE_OR;
    m["STORE_SUBSCR"] = STORE_SUBSCR;
    m["DELETE_SUBSCR"] = DELETE_SUBSCR;
    m["PRINT_EXPR"] = PRINT_EXPR;
    m["BREAK_LOOP"] = BREAK_LOOP;
    m["CONTINUE_LOOP"] = CONTINUE_LOOP;
    m["SET_ADD"] = SET_ADD;
    m["LIST_APPEND"] = LIST_APPEND;
    m["MAP_ADD"] = MAP_ADD;
    m["RETURN_VALUE"] = RETURN_VALUE;
    m["YIELD_VALUE"] = YIELD_VALUE;
    m["IMPORT_STAR"] = IMPORT_STAR;
    m["POP_BLOCK"] = POP_BLOCK;
    m["POP_EXCEPT"] = POP_EXCEPT;
    m["END_FINALLY"] = END_FINALLY;
    m["LOAD_BUILD_CLASS"] = LOAD_BUILD_CLASS;
    m["SETUP_WITH"] = SETUP_WITH;
    m["WITH_CLEANUP"] = WITH_CLEANUP;
    m["STORE_LOCALS"] = STORE_LOCALS;
    m["STORE_NAME"] = STORE_NAME;
    m["DELETE_NAME"] = DELETE_NAME;
    m["UNPACK_SEQUENCE"] = UNPACK_SEQUENCE;
    m["UNPACK_EX"] = UNPACK_EX;
    m["STORE_ATTR"] = STORE_ATTR;
    m["DELETE_ATTR"] = DELETE_ATTR;
    m["STORE_GLOBAL"] = STORE_GLOBAL;
    m["DELETE_GLOBAL"] = DELETE_GLOBAL;
    m["LOAD_CONST"] = LOAD_CONST;
    m["LOAD_NAME"] = LOAD_NAME;
    m["BUILD_TUPLE"] = BUILD_TUPLE;
    m["BUILD_LIST"] = BUILD_LIST;
    m["BUILD_SET"] = BUILD_SET;
    m["BUILD_MAP"] = BUILD_MAP;
    m["LOAD_ATTR"] = LOAD_ATTR;
    m["COMPARE_OP"] = COMPARE_OP;
    m["IMPORT_NAME"] = IMPORT_NAME;
    m["IMPORT_FROM"] = IMPORT_FROM;
    m["JUMP_FORWARD"] = JUMP_FORWARD;
    m["POP_JUMP_IF_TRUE"] = POP_JUMP_IF_TRUE;
    m["POP_JUMP_IF_FALSE"] = POP_JUMP_IF_FALSE;
    m["JUMP_IF_TRUE_OR_POP"] = JUMP_IF_TRUE_OR_POP;
    m["JUMP_IF_FALSE_OR_POP"] = JUMP_IF_FALSE_OR_POP;
    m["JUMP_ABSOLUTE"] = JUMP_ABSOLUTE;
    m["FOR_ITER"] = FOR_ITER;
    m["LOAD_GLOBAL"] = LOAD_GLOBAL;
    m["SETUP_LOOP"] = SETUP_LOOP;
    m["SETUP_EXCEPT"] = SETUP_EXCEPT;
    m["SETUP_FINALLY"] = SETUP_FINALLY;
    m["STORE_MAP"] = STORE_MAP;
    m["LOAD_FAST"] = LOAD_FAST;
    m["STORE_FAST"] = STORE_FAST;
    m["DELETE_FAST"] = DELETE_FAST;
    m["LOAD_CLOSURE"] = LOAD_CLOSURE;
    m["LOAD_DEREF"] = LOAD_DEREF;
    m["STORE_DEREF"] = STORE_DEREF;
    m["DELETE_DEREF"] = DELETE_DEREF;
    m["RAISE_VARARGS"] = RAISE_VARARGS;
    m["CALL_FUNCTION"] = CALL_FUNCTION;
    m["MAKE_FUNCTION"] = MAKE_FUNCTION;
    m["MAKE_CLOSURE"] = MAKE_CLOSURE;
    m["BUILD_SLICE"] = BUILD_SLICE;
    m["EXTENDED_ARG"] = EXTENDED_ARG;
    m["CALL_FUNCTION_VAR"] = CALL_FUNCTION_VAR;
    m["CALL_FUNCTION_KW"] = CALL_FUNCTION_KW;
    m["CALL_FUNCTION_VAR_KW"] = CALL_FUNCTION_VAR_KW;
    m["HAVE_ARGUMENT"] = HAVE_ARGUMENT;
    //New Instructions
    m["BUILD_FUNLIST"] = BUILD_FUNLIST;
    m["SELECT_FUNLIST"] = SELECT_FUNLIST;
    m["CONS_FUNLIST"] = CONS_FUNLIST;
    m["SELECT_TUPLE"] = SELECT_TUPLE;
    return true;
}

unordered_map<string, PyOpCode> OpCodeMap;
bool dummy = create_map(OpCodeMap);

bool create_arg_map(unordered_map<string, int>& m) {
    m["STOP_CODE"] = 0;
    m["NOP"] = 0;
    m["POP_TOP"] = 0;
    m["ROT_TWO"] = 0;
    m["ROT_THREE"] = 0;
    m["DUP_TOP"] = 0;
    m["DUP_TOP_TWO"] = 0;
    m["UNARY_POSITIVE"] = 0;
    m["UNARY_NEGATIVE"] = 0;
    m["UNARY_NOT"] = 0;
    m["UNARY_INVERT"] = 0;
    m["GET_ITER"] = 0;
    m["BINARY_POWER"] = 0;
    m["BINARY_MULTIPLY"] = 0;
    m["BINARY_FLOOR_DIVIDE"] = 0;
    m["BINARY_TRUE_DIVIDE"] = 0;
    m["BINARY_MODULO"] = 0;
    m["BINARY_ADD"] = 0;
    m["BINARY_SUBTRACT"] = 0;
    m["BINARY_SUBSCR"] = 0;
    m["BINARY_LSHIFT"] = 0;
    m["BINARY_RSHIFT"] = 0;
    m["BINARY_AND"] = 0;
    m["BINARY_XOR"] = 0;
    m["BINARY_OR"] = 0;
    m["INPLACE_POWER"] = 0;
    m["INPLACE_MULTIPLY"] = 0;
    m["INPLACE_FLOOR_DIVIDE"] = 0;
    m["INPLACE_TRUE_DIVIDE"] = 0;
    m["INPLACE_MODULO"] = 0;
    m["INPLACE_ADD"] = 0;
    m["INPLACE_SUBTRACT"] = 0;
    m["INPLACE_LSHIFT"] = 0;
    m["INPLACE_RSHIFT"] = 0;
    m["INPLACE_AND"] = 0;
    m["INPLACE_XOR"] = 0;
    m["INPLACE_OR"] = 0;
    m["STORE_SUBSCR"] = 0;
    m["DELETE_SUBSCR"] = 0;
    m["PRINT_EXPR"] = 0;
    m["BREAK_LOOP"] = 0;
    m["CONTINUE_LOOP"] = 1;
    m["SET_ADD"] = 1;
    m["LIST_APPEND"] = 1;
    m["MAP_ADD"] = 1;
    m["RETURN_VALUE"] = 0;
    m["YIELD_VALUE"] = 0;
    m["IMPORT_STAR"] = 0;
    m["POP_BLOCK"] = 0;
    m["POP_EXCEPT"] = 0;
    m["END_FINALLY"] = 0;
    m["LOAD_BUILD_CLASS"] = 0;
    m["SETUP_WITH"] = 1;
    m["WITH_CLEANUP"] = 0;
    m["STORE_LOCALS"] = 0;
    m["STORE_NAME"] = 1;
    m["DELETE_NAME"] = 1;
    m["UNPACK_SEQUENCE"] = 1;
    m["UNPACK_EX"] = 1;
    m["STORE_ATTR"] = 1;
    m["DELETE_ATTR"] = 1;
    m["STORE_GLOBAL"] = 1;
    m["DELETE_GLOBAL"] = 1;
    m["LOAD_CONST"] = 1;
    m["LOAD_NAME"] = 1;
    m["BUILD_TUPLE"] = 1;
    m["BUILD_LIST"] = 1;
    m["BUILD_SET"] = 1;
    m["BUILD_MAP"] = 1;
    m["LOAD_ATTR"] = 1;
    m["COMPARE_OP"] = 1;
    m["IMPORT_NAME"] = 1;
    m["IMPORT_FROM"] = 1;
    m["JUMP_FORWARD"] = 1;
    m["POP_JUMP_IF_TRUE"] = 1;
    m["POP_JUMP_IF_FALSE"] = 1;
    m["JUMP_IF_TRUE_OR_POP"] = 1;
    m["JUMP_IF_FALSE_OR_POP"] = 1;
    m["JUMP_ABSOLUTE"] = 1;
    m["FOR_ITER"] = 1;
    m["LOAD_GLOBAL"] = 1;
    m["SETUP_LOOP"] = 1;
    m["SETUP_EXCEPT"] = 1;
    m["SETUP_FINALLY"] = 1;
    m["STORE_MAP"] = 0;
    m["LOAD_FAST"] = 1;
    m["STORE_FAST"] = 1;
    m["DELETE_FAST"] = 1;
    m["LOAD_CLOSURE"] = 1;
    m["LOAD_DEREF"] = 1;
    m["STORE_DEREF"] = 1;
    m["DELETE_DEREF"] = 1;
    m["RAISE_VARARGS"] = 1;
    m["CALL_FUNCTION"] = 1;
    m["MAKE_FUNCTION"] = 1;
    m["MAKE_CLOSURE"] = 1;
    m["BUILD_SLICE"] = 1;
    m["EXTENDED_ARG"] = 1;
    m["CALL_FUNCTION_VAR"] = 1;
    m["CALL_FUNCTION_KW"] = 1;
    m["CALL_FUNCTION_VAR_KW"] = 1;
    m["HAVE_ARGUMENT"] = 0;
    //New Instructions
    m["BUILD_FUNLIST"] = 1;
    m["SELECT_FUNLIST"] = 0;
    m["CONS_FUNLIST"] = 0;
    m["SELECT_TUPLE"] = 1;
    return true;
}

unordered_map<string, int> ArgMap;
bool dummy2 = create_arg_map(ArgMap);

const char* opcodeNames[] = {
    "STOP_CODE",
    "NOP",
    "POP_TOP",
    "ROT_TWO",
    "ROT_THREE",
    "DUP_TOP",
    "DUP_TOP_TWO",
    "UNARY_POSITIVE",
    "UNARY_NEGATIVE",
    "UNARY_NOT",
    "UNARY_INVERT",
    "GET_ITER",
    "BINARY_POWER",
    "BINARY_MULTIPLY",
    "BINARY_FLOOR_DIVIDE",
    "BINARY_TRUE_DIVIDE",
    "BINARY_MODULO",
    "BINARY_ADD",
    "BINARY_SUBTRACT",
    "BINARY_SUBSCR",
    "BINARY_LSHIFT",
    "BINARY_RSHIFT",
    "BINARY_AND",
    "BINARY_XOR",
    "BINARY_OR",
    "INPLACE_POWER",
    "INPLACE_MULTIPLY",
    "INPLACE_FLOOR_DIVIDE",
    "INPLACE_TRUE_DIVIDE",
    "INPLACE_MODULO",
    "INPLACE_ADD",
    "INPLACE_SUBTRACT",
    "INPLACE_LSHIFT",
    "INPLACE_RSHIFT",
    "INPLACE_AND",
    "INPLACE_XOR",
    "INPLACE_OR",
    "STORE_SUBSCR",
    "DELETE_SUBSCR",
    "PRINT_EXPR",
    "BREAK_LOOP",
    "CONTINUE_LOOP",
    "SET_ADD",
    "LIST_APPEND",
    "MAP_ADD",
    "RETURN_VALUE",
    "YIELD_VALUE",
    "IMPORT_STAR",
    "POP_BLOCK",
    "POP_EXCEPT",
    "END_FINALLY",
    "LOAD_BUILD_CLASS",
    "SETUP_WITH",
    "WITH_CLEANUP",
    "STORE_LOCALS",
    "STORE_NAME",
    "DELETE_NAME",
    "UNPACK_SEQUENCE",
    "UNPACK_EX",
    "STORE_ATTR",
    "DELETE_ATTR",
    "STORE_GLOBAL",
    "DELETE_GLOBAL",
    "LOAD_CONST",
    "LOAD_NAME",
    "BUILD_TUPLE",
    "BUILD_LIST",
    "BUILD_SET",
    "BUILD_MAP",
    "LOAD_ATTR",
    "COMPARE_OP",
    "IMPORT_NAME",
    "IMPORT_FROM",
    "JUMP_FORWARD",
    "POP_JUMP_IF_TRUE",
    "POP_JUMP_IF_FALSE",
    "JUMP_IF_TRUE_OR_POP",
    "JUMP_IF_FALSE_OR_POP",
    "JUMP_ABSOLUTE",
    "FOR_ITER",
    "LOAD_GLOBAL",
    "SETUP_LOOP",
    "SETUP_EXCEPT",
    "SETUP_FINALLY",
    "STORE_MAP",
    "LOAD_FAST",
    "STORE_FAST",
    "DELETE_FAST",
    "LOAD_CLOSURE",
    "LOAD_DEREF",
    "STORE_DEREF",
    "DELETE_DEREF",
    "RAISE_VARARGS",
    "CALL_FUNCTION",
    "MAKE_FUNCTION",
    "MAKE_CLOSURE",
    "BUILD_SLICE",
    "EXTENDED_ARG",
    "CALL_FUNCTION_VAR",
    "CALL_FUNCTION_KW",
    "CALL_FUNCTION_VAR_KW",
    "HAVE_ARGUMENT",
    //New Instructions
    "BUILD_FUNLIST",
    "SELECT_FUNLIST",
    "CONS_FUNLIST",
    "SELECT_TUPLE"
};

const int numOpCodes = sizeof (opcodeNames) / sizeof (char*);

PyByteCode::PyByteCode(string opcode) {
    if (OpCodeMap.find(opcode) == OpCodeMap.end()) {
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Unknown opcode " + opcode + " found in file.");
    }

    this->opcode = OpCodeMap[opcode];
    this->operand = -1;
    this->label = "";
}

PyByteCode::PyByteCode(string opcode, int operand) {
    if (OpCodeMap.find(opcode) == OpCodeMap.end())
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Unknown opcode " + opcode + " found in file.");

    this->opcode = OpCodeMap[opcode];
    this->operand = operand;
    this->label = "";
}

PyByteCode::PyByteCode(string opcode, string label) {
    if (OpCodeMap.find(opcode) == OpCodeMap.end())
        throw new PyException(PYILLEGALOPERATIONEXCEPTION, "Unknown opcode " + opcode + " found in file.");

    this->opcode = OpCodeMap[opcode];
    this->operand = -1;
    this->label = label;
}

PyByteCode::PyByteCode(const PyByteCode& orig) {
    this->opcode = orig.opcode;
    this->operand = orig.operand;
    this->label = orig.label;
}

PyByteCode::~PyByteCode() {
}

PyOpCode PyByteCode::getOpCode() const {
    return this->opcode;
}

int PyByteCode::getOperand() const {
    return this->operand;
}

string PyByteCode::getLabel() const {
    return this->label;
}

string PyByteCode::getOpCodeName() const {
    return opcodeNames[opcode];
}

string PyByteCode::toString() const {
    string result = "          ";
    string opName = getOpCodeName();
    result += opName;

    if (numArgs(opName) > 0) {
        stringstream ss;
        ss << operand;
        string operandStr = ss.str();
        for (int i = 0; i < 32 - opName.size() - operandStr.size(); i++)
            result += " ";
        result += operandStr;
    }
    return result;
}

int PyByteCode::numArgs(string opcode) {
    return ArgMap[opcode];
}