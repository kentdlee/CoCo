/* 
 * File:   PyUtil.h
 * Author: Kent D. Lee
 * (c) 2013
 * Created on February 16, 2013, 10:41 PM
 * 
 * License:
 * Please read the LICENSE file in this distribution for details regarding
 * the licensing of this code. This code is freely available for educational
 * use. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.
 * 
 * Description:
 * This header file is here for any useful functions that the CoCo VM may
 * need to share among the various modules. The printMap template function 
 * below is useful when debugging. 
 */

#ifndef UTIL_H
#define	UTIL_H

#include "PyObject.h"
#include <iostream>
#include <unordered_map>
using namespace std;


template <typename K, typename V>
void printMap(const unordered_map<K, V>& m) {
	typename unordered_map<K,V>::const_iterator it;

        
        for (it=m.begin();it != m.end(); it++) {
             cout << "key: \"" << it->first << "\" "
             << "value: " << it->second << endl;
        }

};

#endif	/* UTIL_H */

