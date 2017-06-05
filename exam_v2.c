#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "checks.h"
#include "gameLog.h"
#include "gui.h"
#include "input.h"


void initializeGame(GameInfo *info);
void updateBoard(GameInfo *info, Position *inputPosition);
void runGame(GameInfo *info);
void exitProgram(GameInfo *info);

int main(void) {
    GameInfo info;
    initializeGame(&info);
    runGame(&info);
    findWinner(&info);
    exitProgram(&info);
    return 0;
}

void initializeGame(GameInfo *info) {
    info->logName = "Othellog.txt";
    initBoard(&info->currentBoard);

    newLog(info->fp, info->logName);
    int numberOfPlayers = getNumberOfPlayers();

    info->player1.field = WHITE;
    info->player2.field = BLACK;

    if (numberOfPlayers == 0) {   //Watch AI's play
        info->player1.name = "Artificial Andy";
        info->player2.name = "Artificial Bob";
        info->player1.ai = info->player2.ai = true;
    } else if (numberOfPlayers == 1) {   //Play with AI
        info->player1.name = malloc(16);
        getUserNameInput(&info->player1);
        info->player1.ai = false;
        info->player2.name = "Artificial Bob";
        info->player2.ai = true;
    } else if (numberOfPlayers == 2) {   //Play 2player game
        info->player1.name = malloc(16);
        getUserNameInput(&info->player1);
        info->player2.name = malloc(16);
        getUserNameInput(&info->player2);
        info->player1.ai = info->player2.ai = false;
    } else {
        printf("Illegal number of players\n");
    }
    initializeGUI(info);
    printBoard(&info->currentBoard);
}

void runGame(GameInfo *info) {
    bool isRunning = true;
    int round = 0;
    Position inputPosition;
    inputPosition.x = 3;
    inputPosition.y = 3;

//Gameloop here
    while (isRunning) {
        if (!setTurn(info, &round)) {
            break;
        }
//Input
        do {
                if (!info->activePlayer->ai) {
                    inputPosition = runGuiPlayerEvents();   //Use this for GUI version

                    //getUserInput(&inputPosition); //Use this for console version
                } else if (info->activePlayer->ai) {
                    getAIInput(&inputPosition);
                }
        } while (isFieldTaken(&info->currentBoard, &inputPosition, false) ||
                 !isMoveLegal(info, &inputPosition, 1));
        printf("%s chose position %c%d\n", info->activePlayer->name, inputPosition.x + 49 + '0', inputPosition.y + 1);

//Logic
        logMove(&inputPosition, info->activePlayer, round, info->fp, info->logName);
        updateBoard(info, &inputPosition);
        if (round >= 70 || isBoardFull(&info->currentBoard))
            isRunning = false;
//Output
        renderGUI(info);
        printBoard(&info->currentBoard);
    }
}

void updateBoard(GameInfo *info, Position *inputPosition) {
    printf("Updating Board \n");
    info->currentBoard.fields[inputPosition->x][inputPosition->y] = info->activePlayer->field;
    isMoveLegal(info, inputPosition, 2);
}

void exitProgram(GameInfo *info) {
    printf("Exiting program\n");

    if (!info->player1.ai)
        free(info->player1.name);

    if (!info->player2.ai)
        free(info->player2.name);

    exitGUI();
}