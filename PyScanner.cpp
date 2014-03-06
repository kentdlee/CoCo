/*
 * Scanner.cpp
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

#include "PyScanner.h"
#include <iostream>
using namespace std;

const char SINGLE_QUOTE = 39;
const int numberOfKeywords = 2;

const string keywd[numberOfKeywords] = {
    string("BEGIN"), string("END")
};

int isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '@');
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int isWhiteSpace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

PyScanner::PyScanner(istream* in) {
    this->in = in;
    this->needToken = true;
    this->colCount = -1;
    this->lineCount = 1;
    this->error = false;
}

PyScanner::~PyScanner() {
    try {
        delete in;
    } catch (...) {}
}

PyToken* PyScanner::getToken() {
    if (!needToken) {
        needToken = true;
        return lastToken;
    }

    PyToken* t;
    int state = 0;
    bool foundOne = false;
    char c;
    string lex;
    int type;
    int k;
    int column, line;

    c = in->get();

    while (!foundOne) {
        colCount++;
        switch (state) {
            case 0:
                lex = "";
                column = colCount;
                line = lineCount;
                if (isLetter(c)) state = 1;
                else if (isDigit(c)) state = 2;
                else if (c == '-') state = 11;
                else if (c == ':') state = 3;
                else if (c == ',') state = 4;
                else if (c == SINGLE_QUOTE) state = 6;
                else if (c == '"') state = 7;
                else if (c == '/') state = 8;
                else if (c == '(') state = 9;
                else if (c == ')') state = 10;
                else if (c == ';') state = 12;
                else if (c == -1) {
                    foundOne = true;
                    type = PYEOFTOKEN;
                } else if (c == '\n') {
                    colCount = -1;
                    lineCount++;
                } else if (isWhiteSpace(c)) {
                } else if (in->eof()) {
                    foundOne = true;
                    type = PYEOFTOKEN;
                } else {
                    if (!error) {
                        cerr << "Unrecognized Character '" << c << "' found at line " << line <<
                                " and column " << column << endl;
                        error = true;
                    }

                    type = PYBADTOKEN;
                    lex = c;
                    foundOne = true;
                }
                break;
            case 1:
                if (isLetter(c) || isDigit(c)) state = 1;
                else {
                    for (k = 0; k < numberOfKeywords; k++)
                        if (lex == keywd[k]) {
                            foundOne = true;
                            type = PYKEYWORDTOKEN;
                        }
                    if (!foundOne) {
                        type = PYIDENTIFIERTOKEN;
                        foundOne = true;
                    }
                }
                break;
            case 2:
                if (isDigit(c)) state = 2;
                else if (c == '.') state = 5;
                else {
                    type = PYINTEGERTOKEN;
                    foundOne = true;
                }
                break;
            case 3:
                type = PYCOLONTOKEN;
                foundOne = true;
                break;
            case 4:
                type = PYCOMMATOKEN;
                foundOne = true;
                break;
            case 5:
                if (isDigit(c)) state = 5;
                else {
                    type = PYFLOATTOKEN;
                    foundOne = true;
                }
                break;
            case 6:
                if (c == SINGLE_QUOTE) {
                    type = PYSTRINGTOKEN;

                    lex = lex + c;
                    //eliminate the quotes on each end.
                    lex = lex.substr(1, lex.size() - 2);
                    c = in->get();
                    foundOne = true;

                    if (in->eof()) {
                        type = PYBADTOKEN;
                    }

                } else {
                    if (in->eof()) {
                        type = PYBADTOKEN;
                        foundOne = true;
                    }
                }

                break;
            case 7:
                if (c == '"') {
                    type = PYSTRINGTOKEN;

                    lex = lex + c;
                    //eliminate the quotes on each end.
                    lex = lex.substr(1, lex.size() - 2);
                    c = in->get();
                    foundOne = true;

                } else {
                    if (in->eof()) {
                        type = PYBADTOKEN;
                        foundOne = true;
                    }
                }
                break;
            case 8:
                foundOne = true;
                type = PYSLASHTOKEN;
                break;
            case 9:
                foundOne = true;
                type = PYLEFTPARENTOKEN;
                break;
            case 10:
                foundOne = true;
                type = PYRIGHTPARENTOKEN;
                break;
            case 11: 
                if (isDigit(c)) 
                    state = 2;
                else {
                    type = PYBADTOKEN;
                    foundOne = true;                    
                }
                break;
            case 12: 
                // Comments extend to end of line and
                // begin with a semicolon.
                if (c == '\n' || c == -1) {
                    colCount = -1;
                    lineCount++;
                    state = 0;
                    lex = "";
                }
                break;
        }

        if (!foundOne) {
            lex = lex + c;
            c = in->get();
        }
    }

    in->putback(c);
    colCount--;
    t = new PyToken(type, lex, line, column);

#ifdef debug
    cerr << "just found " << lex << " with type " << type << endl;
#endif

    lastToken = t;
    return t;

}

void PyScanner::putBackToken() {
    needToken = false;
}
