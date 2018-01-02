/*
 * Kfir Ventura
 * Avihay Arzuan
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
    /**
     * static method to read from file settings for player
     * @param path of file to read from.
     * @return port number
     */
    static int getPort(char * path);
    /**
     * static method to read from file settings for player
     * @param path of file to read from.
     * @return ip string
     */
    static string getIP(char * path);

};

#endif /* SRC_READSETTINGS_H_ */
