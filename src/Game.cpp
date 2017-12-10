/*
 * Kfir Ventura
 * Avihay Arzuan
 */
#include "Game.h"
#include "LocalPlayer.h"

Game::Game() :
		noPosMoves(0), shouldRun(true) {
	this->board = &b;
	this->whitePlayer = NULL;
	this->blackPlayer = NULL;
	this->logic = new DefaultLogic(this->board);
	this->numOfEmptyCells = (this->board->getSize() * this->board->getSize())
			- 4;
	this->currentPlayer = this->blackPlayer;
	this->currentColor = this->currentPlayer->getColor();
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
	if (this->userChoice == humanPlayer) {
		this->blackPlayer = new HumanPlayer(BLACK);
		this->whitePlayer = new HumanPlayer(WHITE);
	} else if (this->userChoice == computerPlayer) {
		this->blackPlayer = new HumanPlayer(BLACK);
		this->whitePlayer = new AIPlayer(WHITE, this->board);
	} else if (this->userChoice == remotePlayer) {
		initRemote();
	}

	play();
}

void Game::initRemote() {
	LocalPlayer *local = new LocalPlayer("127.0.0.1", 8000);

	try {
		local->connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		exit(-1);
	}
	local->setColorFromSocket();
	if (local->getColor() == WHITE) {
		this->whitePlayer = local;
		this->blackPlayer = new RemotePlayer(BLACK);
		this->isLocalTurn = false;
	} else if (local->getColor() == BLACK) {
		this->blackPlayer = local;
		this->whitePlayer = new RemotePlayer(WHITE);
	}
}

void Game::RemoteplayOneTurn() {

}

void Game::play() {
	while (this->shouldRun) {
		playOneTurn();
		this->updateCurrentPlayer();
	}
	this->printWinner();
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

		if (this->noPosMoves == 2)
			this->shouldRun = false;

		return;
	}

	if (userChoice == remotePlayer) {
		if (this->isLocalTurn) {
			this->isLocalTurn = false;
			string move = currentPlayer->makeMove(this->logic, posMoves,
					this->printer);
			this->currentPlayer->sendMessage(move);
		} else {
			this->isLocalTurn = true;

			string remoteMove = this->currentPlayer->readMessage();

			this->logic->executeOrder66(String::parseRow(remoteMove),
					String::parseCol(remoteMove));
		}
	} else {
		currentPlayer->makeMove(this->logic, posMoves, this->printer);
	}

	this->numOfEmptyCells--;
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

void Game::updateCurrentPlayer() {
	if (isCurrentWhite())
		this->updateToBlack();
	else
		this->updateToWhite();

	this->currentColor = this->currentPlayer->getColor();
}

bool Game::isCurrentWhite() const {
	return (this->currentColor == WHITE);
}

void Game::updateToBlack() {
	this->currentPlayer = this->blackPlayer;
}

void Game::updateToWhite() {
	this->currentPlayer = this->whitePlayer;
}

int Game::getScore(char color) const {
	int score = 0;

	for (Iterator iterator = this->board->getCellsList()->begin();
			iterator != this->board->getCellsList()->end(); iterator++)
		if (iterator->second.isFilledWith(color))
			score++;

	return score;
}
