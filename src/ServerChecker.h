/*
 * ServerChecker.h
 *
 *  Created on: Dec 5, 2017
 *      Author: avihay
 */

#ifndef SRC_SERVERCHECKER_H_
#define SRC_SERVERCHECKER_H_



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
//     int sendExercise(int arg1, char op, int arg2);
  private:
     const char *serverIP;
     int serverPort;
     int clientSocket;
 };

#endif /* SRC_SERVERCHECKER_H_ */
