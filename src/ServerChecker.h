/*
 * ServerChecker.h
 *
 *  Created on: Dec 5, 2017
 *      Author: avihay
 */

#ifndef SRC_SERVERCHECKER_H_
#define SRC_SERVERCHECKER_H_
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>



/*
 *
 */
class ServerChecker {
 public:
    ServerChecker(const char *serverIP, int serverPort);
     void connectToServer();
     int sendMessage(char buff[256]);
     int readMessage();
     char getColor();
  private:
     const char *serverIP;
     int serverPort;
     int clientSocket;
     sockaddr_in connectionDetails;
 };

#endif /* SRC_SERVERCHECKER_H_ */
