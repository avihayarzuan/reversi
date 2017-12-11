/*
 * readSettings.h
 *
 *  Created on: Dec 10, 2017
 *      Author: avihay
 */

#ifndef SRC_READSETTINGS_H_
#define SRC_READSETTINGS_H_
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

/*
 *
 */
class ReadSettings {
 public:
     static int getPort(char * path);
     static string getIP(char * path);

};

#endif /* SRC_READSETTINGS_H_ */
