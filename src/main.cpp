/*
 * Kfir Ventura
 * Avihay Arzuan
 */
#include "Game.h"
#include "ReadSettings.h"
#include "ServerChecker.h"

int main() {
//
//    ServerChecker s("127.0.0.1", 7000);
//    try {
//        s.connectToServer();
//    } catch (const char* msg) {
//        cout << "fail " << msg << endl;
//        exit(-1);
//    }
    Game *game = new Game();
    game->run();
    delete game;

    return 0;
}
