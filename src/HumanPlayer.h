/*
 * Kfir Ventura
 * Avihay Arzuan
 */
#ifndef EX2_HUMANPLAYER_H
#define EX2_HUMANPLAYER_H

#include "Player.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

class HumanPlayer : public Player {
 public:
    /**
     * Constructor.
     * @param color - player's color.
     */
    HumanPlayer(char color);

    void setConnection(const char *serverIP, int serverPort);
    void connectToServer();
    int sendMessage(char buff[]);
    int readMessage();
    void setColorFromSocket();
    string getRemoteMove();
    /**
     * @return player's color.
     */
    virtual char getColor() const;

    /**
     * Destructor.
     */
    virtual ~HumanPlayer() {
    }
    ;

    /**
     * The method asks user's choice and responsible to execute it.
     * @param logic - rules of the game.
     * @param posMoves - the possible moves to choose from.
     * @param printer - the console printer.
     */
    string makeMove(GameLogic *logic, map<string, Cell> &posMoves,
                    ConsoleMsgs printer);
 private:
    /**
     * Members.
     */
    char color;
    const char *serverIP;
    int serverPort;
    int clientSocket;
    string remoteMove;
};

#endif //EX2_HUMANPLAYER_H
