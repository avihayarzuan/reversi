/*
 * Kfir Ventura
 * Avihay Arzuan
 */
#include "Game.h"

Game::Game()
        : noPosMoves(0),
          shouldRun(true) {
    this->board = &b;
    this->whitePlayer = NULL;
    this->blackPlayer = NULL;
    this->logic = new DefaultLogic(this->board);
    this->numOfEmptyCells = (this->board->getSize() * this->board->getSize())
            - 4;
    this->currentPlayer = this->blackPlayer;
    this->notCurrentPlayer = this->whitePlayer;
    this->currentColor = BLACK;
    this->userChoice = 0;
    this->isLocalTurn = true;
}

Game::~Game() {
    delete this->logic;
    delete this->blackPlayer;
    delete this->whitePlayer;
}

void Game::run() {
    this->userChoice = this->menu.run();

    if (this->userChoice == remotePlayer) {
        try {
            initRemote();
        } catch (const char *msg) {
            cout << "Cannot initialize Remote game. Reason: " << msg << endl;
            exit(-1);
        }
    } else {
        this->blackPlayer = new HumanPlayer(BLACK);
        this->currentPlayer = this->blackPlayer;

        if (this->userChoice == computerPlayer) {
            this->whitePlayer = new AIPlayer(WHITE, this->board);
        } else {
            this->whitePlayer = new HumanPlayer(WHITE);
        }
    }

    play();
}

void Game::initRemote() {
    // Initialize current player as a new Human Player with no color
    this->currentPlayer = new HumanPlayer(EMPTY);

    // Set the connection and connect to the server, as well as set color
    char buf[] = "settings.txt";
    string ip = ReadSettings::getIP(buf);
    const char * i = ip.c_str();
    int port = ReadSettings::getPort(buf);
    static_cast<HumanPlayer*>(this->currentPlayer)->setConnection(i, port);
    static_cast<HumanPlayer*>(this->currentPlayer)->connectToServer();
    static_cast<HumanPlayer*>(this->currentPlayer)->chooseOption();

// Initializing the second player and setting the current player
    if (this->currentPlayer->getColor() == WHITE) {
        this->whitePlayer = this->currentPlayer;
        this->blackPlayer = new HumanPlayer(BLACK);
        this->currentPlayer = this->blackPlayer;
        this->notCurrentPlayer = this->whitePlayer;
        this->isLocalTurn = false;
    } else if (this->currentPlayer->getColor() == BLACK) {
        this->blackPlayer = this->currentPlayer;
        this->whitePlayer = new HumanPlayer(WHITE);
        this->notCurrentPlayer = blackPlayer;
    }
}

void Game::play() {
    while (this->shouldRun) {
        if (userChoice == remotePlayer) {
            remoteplayOneTurn();
        } else {
            playOneTurn();
        }
        this->updateCurrentPlayer();
    }
    this->printWinner();
    if (userChoice == remotePlayer) {
        endConnection();
    }
}

void Game::remoteplayOneTurn() {
    map<string, Cell> posMoves = logic->getPossibleMoves(this->currentColor);

    this->printer.curBoard(this->board);
    if (!this->numOfEmptyCells) {
        this->shouldRun = false;
        return;
    }
    this->printer.itsYourMove(this->currentColor);
    if (posMoves.size()) {
        this->printer.posMoves(posMoves);
        this->noPosMoves = 0;
    } else {
        this->printer.noPosMoves();
        this->noPosMoves++;
        if (this->noPosMoves == 2) {
            this->shouldRun = false;
            return;
        }
    }

    if (this->isLocalTurn) {

// if there are possiblemoves
        if (posMoves.size()) {
            string move = currentPlayer->makeMove(this->logic, posMoves,
                                                  this->printer);
            string playMove = String::addPlay(move);
            char buf[SIZE];
            strcpy(buf, playMove.c_str());
            try {
                static_cast<HumanPlayer*>(this->currentPlayer)->sendMessage(
                        buf);
            } catch (const char *msg) {
                cout << "Cannot send Message. Reason: " << msg << endl;
                exit(-1);
            }

            // if there are no possiblemoves:
        } else {
            char buf[] = "play no move";
            try {
                static_cast<HumanPlayer*>(this->currentPlayer)->sendMessage(
                        buf);
            } catch (const char *msg) {
                cout << "Cannot send Message. Reason: " << msg << endl;
                exit(-1);
            }
        }
    } else {
        // if it's not local turn:

// if there are possiblemoves
        if (posMoves.size()) {
            try {
                static_cast<HumanPlayer*>(this->notCurrentPlayer)
                        ->readRemoteMove();
            } catch (const char *msg) {
                cout << "Cannot read Message. Reason: " << msg << endl;
                exit(-1);
            }
            string remoteMove =
                    static_cast<HumanPlayer*>(this->notCurrentPlayer)
                            ->getRemoteMove();
            if (remoteMove.compare("closing") == 0) {
                this->shouldRun = false;
            } else {
                this->logic->executeOrder66(String::parseRow(remoteMove),
                                            String::parseCol(remoteMove));
                this->numOfEmptyCells--;
            }

            // if there are no possiblemoves:
        } else {
            try {
                static_cast<HumanPlayer*>(this->notCurrentPlayer)
                        ->readRemoteMove();
                string remoteMove = static_cast<HumanPlayer*>(this
                        ->currentPlayer)->getRemoteMove();
                if (remoteMove.compare("closing") == 0) {
                    this->shouldRun = false;
                } else {
                    cout << remoteMove << endl;
                }
            } catch (const char *msg) {
                cout << "Cannot read Message. Reason: " << msg << endl;
                exit(-1);
            }
        }
    }
}

void Game::playOneTurn() {
    map<string, Cell> posMoves = logic->getPossibleMoves(this->currentColor);
    this->printer.curBoard(this->board);
    if (!this->numOfEmptyCells) {
        this->shouldRun = false;
        return;
    }
    this->printer.itsYourMove(this->currentColor);
    if (posMoves.size()) {
        this->printer.posMoves(posMoves);
        this->noPosMoves = 0;
    } else {
        this->printer.noPosMoves();
        this->noPosMoves++;
        if (this->noPosMoves == 2) {
            this->shouldRun = false;
        }
        return;
    }
    currentPlayer->makeMove(this->logic, posMoves, this->printer);
    this->numOfEmptyCells--;
}

void Game::endConnection() {
    string name = static_cast<HumanPlayer*>(this->currentPlayer)->getGameName();
    char buf[SIZE];
    strcpy(buf, "close ");
    strcat(buf, name.c_str());
    try {
        int stat = static_cast<HumanPlayer*>(this->currentPlayer)->sendMessage(
                buf);
        if (stat < 0) {
            cout << "Game ended - disconnected from server" << endl;
        }
    } catch (const char *msg) {
        cout << "Cannot send Message. Reason: " << msg << endl;
        exit(-1);
    }
}

void Game::updateCurrentPlayer() {
    if (isCurrentWhite()) {
        this->updateToBlack();
    } else {
        this->updateToWhite();
    }

    this->currentColor = this->currentPlayer->getColor();

    if (userChoice == remotePlayer) {
        if (isLocalTurn) {
            this->isLocalTurn = false;
        } else {
            this->isLocalTurn = true;
        }
    }
}

void Game::printWinner() const {
    int blackScore = this->getScore(blackPlayer->getColor());
    int whiteScore = this->getScore(whitePlayer->getColor());

    if (blackScore > whiteScore)
        this->printer.printWinner(BLACK);
    else if (blackScore < whiteScore)
        this->printer.printWinner(WHITE);
    else
        this->printer.printWinner(EMPTY);
}

bool Game::isCurrentWhite() const {
    return (this->currentColor == WHITE);
}

void Game::updateToBlack() {
    this->currentPlayer = this->blackPlayer;
    this->notCurrentPlayer = this->whitePlayer;
}

void Game::updateToWhite() {
    this->currentPlayer = this->whitePlayer;
    this->notCurrentPlayer = this->blackPlayer;
}

int Game::getScore(char color) const {
    int score = 0;

    for (Iterator iterator = this->board->getCellsList()->begin();
            iterator != this->board->getCellsList()->end(); iterator++)
        if (iterator->second.isFilledWith(color))
            score++;

    return score;
}
