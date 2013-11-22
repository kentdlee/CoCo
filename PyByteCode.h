/* 
 * File:   PyByteCode.h
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
 * The PyByteCode class is used for byte codes of compiled functions in the 
 * virtual machine. Each byte code read from the source file is parsed along 
 * with its operand and a corresponding object is created to hold the
 * byte codes information. While parsing the assembly language file, branch
 * and jump instructions will likely have a label as their target. This label
 * is stored here in the bytecode object. A second pass, once all instructions 
 * are read and parsed from the input file, sets the necessary operand for the 
 * target of the label. 
 * 
 * IMPORTANT NOTE: 
 * In the original Python Virtual Machine the operand (i.e. target) of a branch
 * or jump instruction was either relative to the current Program Counter (PC) 
 * absolute. In CoCo all operands are absolute regardless of instruction type. 
 */

#ifndef PYBYTECODE_H
#define	PYBYTECODE_H

#include<string>
using namespace std;

enum PyOpCode {
    STOP_CODE,
    NOP,
    POP_TOP,
    ROT_TWO,
    ROT_THREE,
    DUP_TOP,
    DUP_TOP_TWO,
    UNARY_POSITIVE,
    UNARY_NEGATIVE,
    UNARY_NOT,
    UNARY_INVERT,
    GET_ITER,
    BINARY_POWER,
    BINARY_MULTIPLY,
    BINARY_FLOOR_DIVIDE,
    BINARY_TRUE_DIVIDE,
    BINARY_MODULO,
    BINARY_ADD,
    BINARY_SUBTRACT,
    BINARY_SUBSCR,
    BINARY_LSHIFT,
    BINARY_RSHIFT,
    BINARY_AND,
    BINARY_XOR,
    BINARY_OR,
    INPLACE_POWER,
    INPLACE_MULTIPLY,
    INPLACE_FLOOR_DIVIDE,
    INPLACE_TRUE_DIVIDE,
    INPLACE_MODULO,
    INPLACE_ADD,
    INPLACE_SUBTRACT,
    INPLACE_LSHIFT,
    INPLACE_RSHIFT,
    INPLACE_AND,
    INPLACE_XOR,
    INPLACE_OR,
    STORE_SUBSCR,
    DELETE_SUBSCR,
    PRINT_EXPR,
    BREAK_LOOP,
    CONTINUE_LOOP,
    SET_ADD,
    LIST_APPEND,
    MAP_ADD,
    RETURN_VALUE,
    YIELD_VALUE,
    IMPORT_STAR,
    POP_BLOCK,
    POP_EXCEPT,
    END_FINALLY,
    LOAD_BUILD_CLASS,
    SETUP_WITH,
    WITH_CLEANUP,
    STORE_LOCALS,
    STORE_NAME,
    DELETE_NAME,
    UNPACK_SEQUENCE,
    UNPACK_EX,
    STORE_ATTR,
    DELETE_ATTR,
    STORE_GLOBAL,
    DELETE_GLOBAL,
    LOAD_CONST,
    LOAD_NAME,
    BUILD_TUPLE,
    BUILD_LIST,
    BUILD_SET,
    BUILD_MAP,
    LOAD_ATTR,
    COMPARE_OP,
    IMPORT_NAME,
    IMPORT_FROM,
    JUMP_FORWARD,
    POP_JUMP_IF_TRUE,
    POP_JUMP_IF_FALSE,
    JUMP_IF_TRUE_OR_POP,
    JUMP_IF_FALSE_OR_POP,
    JUMP_ABSOLUTE,
    FOR_ITER,
    LOAD_GLOBAL,
    SETUP_LOOP,
    SETUP_EXCEPT,
    SETUP_FINALLY,
    STORE_MAP,
    LOAD_FAST,
    STORE_FAST,
    DELETE_FAST,
    LOAD_CLOSURE,
    LOAD_DEREF,
    STORE_DEREF,
    DELETE_DEREF,
    RAISE_VARARGS,
    CALL_FUNCTION,
    MAKE_FUNCTION,
    MAKE_CLOSURE,
    BUILD_SLICE,
    EXTENDED_ARG,
    CALL_FUNCTION_VAR,
    CALL_FUNCTION_KW,
    CALL_FUNCTION_VAR_KW,
    HAVE_ARGUMENT,
    //Here are some new opcodes that Kent Lee has defined.
    BUILD_FUNLIST,
    SELECT_FUNLIST, // TOS1 is PyFunList of tail of list, TOS is head of list
    CONS_FUNLIST,
    SELECT_TUPLE //TOS to TOSn where n is the length of tuple. TOS is left-most element.
};

class PyByteCode {
public:
    PyByteCode(string opcode);
    PyByteCode(string opcode, int operand);
    PyByteCode(string opcode, string label);
    PyByteCode(const PyByteCode& orig);
    virtual ~PyByteCode();
    PyOpCode getOpCode() const;
    int getOperand() const;
    string getOpCodeName() const;
    string getLabel() const;
    string toString() const;
    static int numArgs(string opcode);
    
private:
    PyOpCode opcode;
    int operand;
    string label;
};

#endif	/* PYBYTECODE_H */

