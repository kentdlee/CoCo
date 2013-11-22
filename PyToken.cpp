/*
 * PyToken.cpp
 * Author: Kent D. Lee
 * (c) 2013
 * Created on: Feb 7, 2013
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

#include "PyToken.h"

PyToken::PyToken(int tokenType, string lex, int line, int col) {
	this->lexeme = lex;
	this->tokenType = tokenType;
	this->line = line;
	this->column = col;
}

PyToken::~PyToken() {}

int PyToken::getType() const {
	return tokenType;
}

string PyToken::getLex() const {
	return lexeme;
}

int PyToken::getCol() const {
	return column;
}

int PyToken::getLine() const {
	return line;
}



