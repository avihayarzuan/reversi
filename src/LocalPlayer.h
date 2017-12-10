/*
 * LocalPlayer.h
 *
 *  Created on: Dec 8, 2017
 *      Author: avihay
 */

#ifndef SRC_LOCALPLAYER_H_
#define SRC_LOCALPLAYER_H_

#include "Player.h"
#include "ConsoleMsgs.h"
#include "GameLogic.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*
 *
 */
class LocalPlayer : public Player {
 public:
    LocalPlayer(const char *serverIP, int serverPort);
    void connectToServer();
    int sendMessage(char buff[256]);
    int readMessage();
    virtual char getColor() const;
    void setColorFromSocket();
    string makeMove(GameLogic *logic, map<string, Cell> &posMoves,
                          ConsoleMsgs printer);
    virtual ~LocalPlayer();
 private:
    char color;
    const char *serverIP;
    int serverPort;
    int clientSocket;
};

#endif /* SRC_LOCALPLAYER_H_ */
