/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: avihay
 */

#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(char color)
        : color(color) {
}

RemotePlayer::~RemotePlayer() {
}

string RemotePlayer::makeMove(GameLogic *logic, map<string, Cell> &posMoves,
                           ConsoleMsgs printer) {
    string move;
    this->makeRemoteMove(logic, move);
    return move;
}

void RemotePlayer::makeRemoteMove(GameLogic *logic, string move) {
    logic->executeOrder66(String::parseRow(move), String::parseCol(move));
}

char RemotePlayer::getColor() const{
    return this->color;
}
