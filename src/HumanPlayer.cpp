/*
 * Kfir Ventura
 * Avihay Arzuan
 */
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(char color)
        : color(color) {
    this->serverIP = NULL;
    this->serverPort = 0;
    this->clientSocket = 0;
}

void HumanPlayer::setConnection(const char *serverIP, int serverPort) {
    this->serverIP = serverIP;
    this->serverPort = serverPort;
}

void HumanPlayer::connectToServer() {
    // Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (const struct sockaddr *) &serverAddress,
                sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl;
}

int HumanPlayer::sendMessage(char buff[]) {
    int stat;
    stat = write(clientSocket, buff, sizeof(char) * SIZE);
    if (stat == -1) {
        throw "Error writing message to socket";
    }
    return stat;
}

int HumanPlayer::readRemoteMove() {
    int stat;
    char returnBuff[SIZE];
    stat = read(clientSocket, returnBuff, sizeof(char) * SIZE);
    if (stat == -1) {
        throw "Error reading message from socket";
    }
    if (strcmp(returnBuff, "closing") == 0) {
        cout << "Server is shutting down" << endl;
    } else {
        cout << returnBuff << endl;
    }
    this->remoteMove = returnBuff;
    return stat;
}

string HumanPlayer::getRemoteMove() {
    return this->remoteMove;
}

ArrayHolder HumanPlayer::readMessage() {
    int stat;
    ArrayHolder ah;
    char returnBuff[SIZE];
    stat = read(clientSocket, returnBuff, sizeof(char) * SIZE);
    if (stat == -1) {
        throw "Error reading message from socket";
    }
    strcpy(ah.array, returnBuff);
    return ah;
}

void HumanPlayer::chooseOption() {
    bool choosing = true;
    while (choosing) {
        cout << "Please press the number of the following options:" << endl;
        cout << "1. Start a new game" << endl;
        cout << "2. Get the list of possibles games" << endl;
        cout << "3. Join available game" << endl;
        int choice;
        ArrayHolder msg;
        char buf1[MAX_MESSAGE];
        char buf2[MAX_MESSAGE];
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cin >> choice;
        if (choice != 0) {
            if (choice == 1) {
                char start[MAX_MESSAGE];
                cout << "Please type your game name:" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cin.getline(buf1, sizeof(buf1));
                this->gameName = buf1;
                strcpy(start, "start ");
                strcat(start, buf1);
                sendMessage(start);
                msg = readMessage();
                if (msg.array[0] == '-' && msg.array[1] == '1') {
                    cout << "the game name already exist" << endl;
                } else if (msg.array[0] == '1') {
                    buf2[0] = '1';
                    buf2[1] = '\0';
                    sendMessage(buf2);
                    cout << "waiting for other player to connect game" << endl;
                    setColorFromSocket();
                    choosing = false;
                }
            } else if (choice == 2) {
                strcpy(buf2, "list_games ");
                sendMessage(buf2);
                msg = readMessage();
                for (int i = 0; i < MAX_MESSAGE; i++) {
                    if (msg.array[i] == '\0') {
                        break;
                    } else {
                        cout << msg.array[i];
                    }
                }
            } else if (choice == 3) {
                char join[MAX_MESSAGE];
                cout << "Please type game name to join:" << endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cin.getline(buf1, sizeof(buf1));
                this->gameName = buf1;
                strcpy(join, "join ");
                strcat(join, buf1);
                sendMessage(join);
                msg = readMessage();
                if (msg.array[0] == '-' && msg.array[1] == '1') {
                    cout << "the game name not exist" << endl;
                } else if (msg.array[0] == '1') {
                    buf2[0] = '1';
                    buf2[1] = '\0';
                    sendMessage(buf2);
                    setColorFromSocket();
                    choosing = false;
                }
            }
        }
    }
}

void HumanPlayer::setColorFromSocket() {
    int stat;
    char buff[SIZE] = { 0 };
    stat = read(clientSocket, buff, sizeof(char) * SIZE);
    if (stat == -1) {
        throw "Error get color";
    }
    char answer = buff[0];
    this->color = answer;
    cout << "you are color: " << answer << endl;
}

char HumanPlayer::getColor() const {
    return this->color;
}

string HumanPlayer::getGameName() const {
    return this->gameName;
}

string HumanPlayer::makeMove(GameLogic *logic, map<string, Cell> &posMoves,
                             ConsoleMsgs printer) {
    int row, col;
    do {
        cout << "please enter row: " << endl;
        cin >> row;
        int x = isdigit(row);
        if (x == 0) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "please enter column: " << endl;
            cin >> col;
            if (isdigit(col) == 0) {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                if (posMoves.count(String::intToPoint(row, col)))
                    break;
            }
        }
        printer.illegalMove();
    } while (true);
    string move;
    logic->executeOrder66(row, col);
    move = String::intToPoint(row, col);
    return move;
}
