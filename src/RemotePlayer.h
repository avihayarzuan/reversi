/*
 * RemotePlayer.h
 *
 *  Created on: Dec 8, 2017
 *      Author: avihay
 */

#ifndef SRC_REMOTEPLAYER_H_
#define SRC_REMOTEPLAYER_H_

#include "Player.h"

/*
 *
 */
class RemotePlayer : public Player{
 public:
    RemotePlayer(char color);
    string makeMove(GameLogic *logic, map<string, Cell> &posMoves,
                              ConsoleMsgs printer);
    void makeRemoteMove(GameLogic *logic, string move);
    virtual char getColor() const;
    virtual ~RemotePlayer();
 private:
    char color;
};

#endif /* SRC_REMOTEPLAYER_H_ */
