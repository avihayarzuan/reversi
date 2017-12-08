/*
 * Kfir Ventura
 * Avihay Arzuan
 */

#include "MainMenu.h"

MainMenu::MainMenu() {
}

MainMenu::~MainMenu() {
}

bool MainMenu::checkUserChoice(int &choice) {
    if (choice != humanPlayer && choice != computerPlayer && choice != remotePlayer) {
        cout << "Wrong choice! Please try again!" << endl;
        return true;
    }
    return false;
}

void MainMenu::printUserChoice(int &choice) {
    cout << "You chose to play with:"<< endl;
    if (choice == remotePlayer) {
        cout << "remote player!" << endl<< endl;
    } else if (choice == humanPlayer)
        cout << "human player!"  << endl<< endl;
    else {
        cout << "computer player!"  << endl<< endl;
    }
}

userChoice MainMenu::run() {
    cout << "Choose game mode:" << endl;
    cout << "Press " << humanPlayer << " for human player " << endl;
    cout << "Press " << computerPlayer << " for computer player." << endl;
    cout << "Press " << remotePlayer << " for remote player." << endl;

    int choice = humanPlayer;
    do {
        cin >> choice;
    } while (checkUserChoice(choice));

    printUserChoice(choice);

    return (userChoice) choice;
}
