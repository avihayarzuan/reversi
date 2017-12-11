/*
 * readSettings.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: avihay
 */

#include "ReadSettings.h"

int ReadSettings::getPort(char * path) {
    int port = -1;
    ifstream file;
    file.open(path);
    if (file.is_open()) {
        string line;
        getline(file, line);
        int start = line.find("(");
        int end = line.find(")");
        int diff = (end - start);
        string num = line.substr(start + 1, (diff - 1));
        port = atoi(num.c_str());
        file.close();
    }
    return port;
}

string ReadSettings::getIP(char * path) {
    string IP = "error getting IP from file";
    ifstream file;
    file.open(path);
    if (file.is_open()) {
        string dummyLine;
        string line;
        getline(file, dummyLine);
        getline(file, line);
        int start = line.find("(");
        int end = line.find(")");
        int diff = (end - start);
        IP = line.substr(start + 1, (diff - 1));
        file.close();
    }
    return IP;
}

