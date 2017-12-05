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
#include "Client.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
    Client client("127.0.0.1", 8000);
    try {
        client.connectToServer();
    } catch (const char *msg) {
        cout << "Failed to connect to server. Reason:" << msg << endl;
        exit(-1);
    }
    int num1, num2;
    char op;
    while (true) {
        cout << "Enter an exercise (e.g., 15*19):";
        cin >> num1 >> op >> num2;
        cout << "Sending exercise: " << num1 << op << num2 << endl;
        try {
            int result = client.sendExercise(num1, op, num2);
            cout << "Result: " << result << endl;
        } catch (const char *msg) {
            cout << "Failed to send exercise to server.Reason: " << msg << endl;
        }
    }
}
