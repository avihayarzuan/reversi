/*
 * Kfir Ventura
 * Avihay Arzuan
 */

#include "AIPlayer.h"

AIPlayer::AIPlayer(char color, Board *b)
        : color(color),
          board(b) {
}

char AIPlayer::getColor() const {
    return this->color;
}

string AIPlayer::makeMove(GameLogic *logic, map<string, Cell> &posMoves,
                          ConsoleMsgs printer) {
    char oppColor;
    string move;
    if (this->color == BLACK) {
        oppColor = WHITE;
    } else {
        oppColor = BLACK;
    }
    if (posMoves.size() == 1) {
        logic->executeOrder66(posMoves.begin()->second.getRow(),
                              posMoves.begin()->second.getRow());
        move = String::intToPoint(posMoves.begin()->second.getRow(),
                                  posMoves.begin()->second.getRow());
    } else {
        move = MiniMaxAlgo::useMiniMaxMove(logic, posMoves, this->color, oppColor,
                                    this->board);
    }
    return move;
}
