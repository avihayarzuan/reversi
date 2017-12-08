/*
 * ServerChecker.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: avihay
 */

#include "ServerChecker.h"

#include "ServerChecker.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

using namespace std;
ServerChecker::ServerChecker(const char *serverIP, int serverPort)
        : serverIP(serverIP),
          serverPort(serverPort),
          clientSocket(0) {
    cout << "ServerChecker" << endl;
}

void ServerChecker::connectToServer() {
    // Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *) &serverAddress,
                sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
}

char ServerChecker::getColor() {
    int stat;
    char buff[256];
    stat = read(clientSocket, buff, sizeof(char) * 256);
    if (stat == -1) {
        throw "Error get color";
    }
    char answer = buff[0];
    cout << answer << endl;
    return answer;
}
int ServerChecker::sendMessage(char buff[]) {
    int stat;
    stat = write(clientSocket, buff, sizeof(char) * 256);
    if (stat == -1) {
        throw "Error writing arg1 to socket";
    }
    return stat;
}
int ServerChecker::readMessage() {
    int stat;
    char buff[256];
    stat = read(clientSocket, buff, sizeof(char) * 256);
    if (stat == -1) {
        throw "Error reading result from socket";
    }
    cout << buff << endl;
    return stat;
}

//int ServerChecker::sendExercise(int arg1, char op, int arg2) {
//    // Write the exercise arguments to the socket
//    int n = write(clientSocket, &arg1, sizeof(arg1));
//    if (n == -1) {
//        throw "Error writing arg1 to socket";
//    }
//    n = write(clientSocket, &op, sizeof(op));
//    if (n == -1) {
//        throw "Error writing op to socket";
//    }
//    n = write(clientSocket, &arg2, sizeof(arg2));
//    if (n == -1) {
//        throw "Error writing arg2 to socket";
//    }
//    // Read the result from the server
//    int result;
//    n = read(clientSocket, &result, sizeof(result));
//    if (n == -1) {
//        throw "Error reading result from socket";
//    }
//    return result;
//}
