/*
 * Kfir Ventura
 * Avihay Arzuan
 */
#include "String.h"

string String::intToPoint(int x, int y) {
    char rowString[4], colString[4];
    string str = "";

    sprintf(rowString, "%d", x);
    sprintf(colString, "%d", y);

    return str + '(' + rowString + ',' + colString + ')';
}

string String::addPlay(string move) {
    string play = "play";
    int x = parseRow(move);
    int y = parseCol(move);
    char rowString[4], colString[4];

    sprintf(rowString, "%d", x);
    sprintf(colString, "%d", y);

    return play + ' ' + rowString + ' ' + colString;
}

int String::parseRow(string move) {
    string rowStr;

    for (string::iterator iter = move.begin(); iter != move.end(); iter++) {
        if (*iter.base() == '(')
            continue;

        if (*iter.base() == ',')
            break;

        rowStr += *iter.base();
    }

    return stoi(rowStr);
}

int String::parseCol(string move) {
    string colStr;
    bool commaNotMet = true;

    for (string::iterator iter = move.begin(); iter != move.end(); iter++) {
        while (commaNotMet) {
            if (*iter.base() == ',')
                commaNotMet = false;
            iter++;
        }

        if (*iter.base() == ',')
            iter++;

        if (*iter.base() == ')')
            break;

        colStr += *iter.base();
    }

    return stoi(colStr);
}

int String::stoi(string str) {
    string::iterator iter = str.begin();

    return atoi(iter.base());
}
