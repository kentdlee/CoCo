/*
 * Scanner.h
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
 * The PyScanner class provides a lexical analyzer for the PyParser class. 
 * When getToken is called on the scanner, the next token of the input file
 * is returned. The CoCo assembly language is LL(1). This means that we can 
 * parse it with a recursive descent parser with one symbol of look-ahead. 
 * The putBackToken method below will put the last token back so it can 
 * be retrieved again later with getToken. Calling putBackToken multiple 
 * times has no accumulative effect. Only the last token can be put back. 
 */

#ifndef PYSCANNER_H_
#define PYSCANNER_H_

#include <fstream>
#include "PyToken.h"

using namespace std;

class PyScanner {
public:
	PyScanner(istream* in);
	virtual ~PyScanner();
	PyToken* getToken();
	void putBackToken();

private:
	istream* in;
	PyToken* lastToken;
	bool needToken;
	int colCount;
	int lineCount;
        bool error;
};

#endif /* SCANNER_H_ */
