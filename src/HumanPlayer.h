/*
 * Kfir Ventura
 * Avihay Arzuan
 */
#ifndef EX2_HUMANPLAYER_H
#define EX2_HUMANPLAYER_H
#define SIZE 256
#define MAX_MESSAGE 256


#include "Player.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct ArrayHolder
{
    char array[MAX_MESSAGE];
};


class HumanPlayer : public Player {
 public:
    /**
     * Constructor.
     * @param color - player's color.
     */
    HumanPlayer(char color);
    /**
     *
     * @param serverIP the ip of the server
     * @param serverPort the server port number
     */
    void setConnection(const char *serverIP, int serverPort);
    /**
     * the function connect to server
     */
    void connectToServer();

    void chooseOption();

    ArrayHolder readMessage();

    /**
     *
     * @param buff the message to send
     * @return int the status number for the write function
     */
    int sendMessage(char buff[]);
    /**
     *
     * @return status of the read function
     */
    int readRemoteMove();
    /**
     * set the color of the player from the message of the server
     */
    void setColorFromSocket();
    /**
     *
     * @return the move that was added by the read message function
     */
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

    string getGameName() const;
 private:
    /**
     * Members.
     */
    char color;
    const char *serverIP;
    int serverPort;
    int clientSocket;
    string remoteMove;
    string gameName;
};

#endif //EX2_HUMANPLAYER_H
