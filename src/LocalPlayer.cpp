/*
 * LocalPlayer.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: avihay
 */

#include "LocalPlayer.h"

LocalPlayer::LocalPlayer(const char *serverIP, int serverPort)
        : serverIP(serverIP),
          serverPort(serverPort),
          clientSocket(0), color(0) {
}

LocalPlayer::~LocalPlayer() {
}

void LocalPlayer::connectToServer() {
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

void LocalPlayer::setColorFromSocket() {
    int stat;
    char buff[256];
    stat = read(clientSocket, buff, sizeof(char) * 256);
    if (stat == -1) {
        throw "Error get color";
    }
    char answer = buff[0];
    this->color = answer;
//    return answer;
}

int LocalPlayer::sendMessage(char buff[]) {
    int stat;
    stat = write(clientSocket, buff, sizeof(char) * 256);
    if (stat == -1) {
        throw "Error writing message to socket";
    }
    return stat;
}

int LocalPlayer::readMessage() {
    int stat;
    char buff[256];
    stat = read(clientSocket, buff, sizeof(char) * 256);
    if (stat == -1) {
        throw "Error reading message from socket";
    }
    cout << buff << endl;
    return stat;
}

char LocalPlayer::getColor() const {
    return this->color;
}

string LocalPlayer::makeMove(GameLogic *logic, map<string, Cell> &posMoves,
                           ConsoleMsgs printer) {
    int row, col;
    do {
        cout << "please enter row: " << endl;
        cin >> row;
        int x = isdigit(row);
        if (x == 0) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "please enter column: " << endl;
            cin >> col;
            if (isdigit(col) == 0) {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                if (posMoves.count(String::intToPoint(row, col)))
                    break;
            }
        }
        printer.illegalMove();
        //printer->plsEnterMove();
    } while (true);
    string move;
    logic->executeOrder66(row, col);
    move = String::intToPoint(row, col);
    return move;
}