/*
 * Kfir Ventura
 * Avihay Arzuan
 */

#ifndef EX2_STRING_H
#define EX2_STRING_H

#include <string>
#include <cstdio>
#include <stdlib.h>

using namespace std;

class String {
 public:
  /**
   * The method converts two int values into a string point format "(x,y)".
   * @param x - x coordinate
   * @param y - y coordinate
   * @return "(x,y)"
   */
  static string intToPoint(int x, int y);
  /**
   * parse the row int from the string move
   * from '(X, Y)' TO X
   * @param move string to parse from
   * @return the row int
   */
  static int parseRow(string move);
  /**
   * parse the column int from the string move
   * from '(X, Y)' TO Y
   * @param move string to parse from
   * @return the column int
   */
  static int parseCol(string move);
  /**
   * add the string play to given point
   * (X, Y) to "play X Y"
   * @param move string add to
   * @return string "play X Y"
   */
  static string addPlay(string move);
 private:
  static int stoi(string str);
};

#endif //EX2_STRING_H
