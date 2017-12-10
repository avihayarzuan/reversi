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

    void setConnection(char *serverIP, int serverPort);
    void connectToServer();
    int sendMessage(char*&buff);
    int readMessage(char* &buff);
    void setColorFromSocket();
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
    char *serverIP;
    int serverPort;
    int clientSocket;
};

#endif //EX2_HUMANPLAYER_H
