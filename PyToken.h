/*
 * PyToken.h
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
 * This class defines tokens that are returned by the PyScanner to the 
 * PyParser when CoCo reads and parses an assembly language (casm) file. 
 */

#ifndef PYTOKEN_H_
#define PYTOKEN_H_

#include <string>

using namespace std;

class PyToken {
public:
	PyToken(int tokenType, string lex, int line, int col);
	virtual ~PyToken();
	string getLex() const;
	int getType() const;
	int getCol() const;
	int getLine() const;

private:
	string lexeme;
	int tokenType;
	int line;
	int column;
};

const int PYIDENTIFIERTOKEN = 1;
const int PYINTEGERTOKEN = 2;
const int PYFLOATTOKEN = 3;
const int PYSTRINGTOKEN = 4;
const int PYKEYWORDTOKEN = 5;
const int PYCOLONTOKEN = 6;
const int PYCOMMATOKEN = 7;
const int PYSLASHTOKEN = 8;
const int PYLEFTPARENTOKEN = 9;
const int PYRIGHTPARENTOKEN = 10;
const int PYEOFTOKEN = 98;
const int PYBADTOKEN = 99;

#endif /* PYTOKEN_H_ */
