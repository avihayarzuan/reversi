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
  static string intToPoint(int x, int y); // to '(x, y)'
  static int parseRow(string move); // from '(X, Y)' TO X
  static int parseCol(string move); // from '(X, Y)' TO Y
  static string addPlay(string move); // (X, Y) to "play X Y"
 private:
  static int stoi(string str);
};

#endif //EX2_STRING_H
