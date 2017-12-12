/*
 * Kfir Ventura
 * Avihay Arzuan
 */
#include "Game.h"
#include "ReadSettings.h"

int main() {
    Game *game = new Game();
    game->run();
    delete game;
    return 0;
}
