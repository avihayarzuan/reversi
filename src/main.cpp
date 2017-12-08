/*
 * Kfir Ventura
 * Avihay Arzuan
 */
//#include "Game.h"
//
//int main() {
//  Game *game = new Game();
//  game->run();
//  delete game;
//
//  return 0;
//}
#include "ServerChecker.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
    bool myTurn = true;
    ServerChecker client("127.0.0.1", 8000);
    try {
        client.connectToServer();
    } catch (const char *msg) {
        cout << "Failed to connect to server. Reason:" << msg << endl;
        exit(-1);
    }
        char buff[256];
    if (client.getColor() == 'O') {
        myTurn = false;
    }
    while (myTurn) {
        cout << "Enter message:" <<endl;
        cin >> buff;
        cout << "Sending message: " << buff << endl;
        client.sendMessage(buff);
        client.readMessage();
    }
    while (!myTurn) {
            client.readMessage();
            cout << "Enter message:" <<endl;
            cin >> buff;
            cout << "Sending message: " << buff << endl;
            client.sendMessage(buff);
        }

}
