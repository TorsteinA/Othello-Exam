//
// Created by torsteinalvern on 14/12/16.
//

#include "board.h"
#include "utilities.h"
#include "checks.h"
#include "gameLog.h"


int charToInt(char c)
{
    char CharConstant[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    short size = sizeof(CharConstant) / sizeof(CharConstant[0]);

    for (short i = 0; i < size; i++) {
        if (CharConstant[i] == c) {
            return i;
        }
    }
    return -1;
}

void flipTiles(GameInfo *info, Position *inputPosition, int x, int y, int distance)
{
    Position checkPosition;
    printf("distance: %d\n", distance);

    for (int i = distance - 1; i > 0; i--) {
        if (!isInsideBorder(inputPosition, x * i, y * i, 1)) {
            //printf("Checked area is outside board\n");
        } else {
            checkPosition.x = inputPosition->x + (x * i);
            checkPosition.y = inputPosition->y + (y * i);
            printf("\tDistance now %d, flipping position x: %d, y: %d\n", i, checkPosition.x, checkPosition.y);
            flipTile(info, &checkPosition);
        }

    }
}

void flipTile(GameInfo *info, Position *position)
{
    if (info->currentBoard.fields[position->x][position->y] == BLACK) {
        printf("\tTile set to White!\n");
        info->currentBoard.fields[position->x][position->y] = WHITE;
    } else if (info->currentBoard.fields[position->x][position->y] == WHITE) {
        printf("\tTile set to Black!\n");
        info->currentBoard.fields[position->x][position->y] = BLACK;
    } else if (info->currentBoard.fields[position->x][position->y] == EMPTY) {
        printf("Couldn't flip tile because it's empty\n");
    } else {
        printf("Failed to flip tile\n");
    }
}

void findWinner(GameInfo *info)
{
    printf("Finding winner\n");
    int player1Count = 0;
    int player2Count = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            //printf("Checking tile at x: %c, y: %d\n", i +49 + '0', j+1); //converts x to char, and y to value on board.
            if (info->currentBoard.fields[i][j] == WHITE) {
                player1Count++;
            } else if (info->currentBoard.fields[i][j] == BLACK) {
                player2Count++;
            }
        }
    }
    if (player1Count > player2Count) {
        printf("%s wins!\nScore: %d\n\n\n", info->player1.name, player1Count);
        finishLog(info->player1.name, player1Count, info->fp, info->logName);
    } else if (player1Count < player2Count) {
        printf("%s wins!\nScore: %d\n\n\n", info->player2.name, player2Count);
        finishLog(info->player2.name, player2Count, info->fp, info->logName);
    } else if (player1Count == player2Count) {
        printf("It's a draw!\n");
        finishLog("", 0, info->fp, info->logName);
    } else {
        printf("Something went wrong when trying to find winner!");
    }
}

bool setTurn(GameInfo *info, int *round)
{
    bool flagIsSet = false;
    bool success = false;

    do {
        printf("\n\nRound %d!\n", ++*round);

        if (*round % 2 == 1) {
            info->activePlayer = &info->player1;
            info->enemyPlayer = &info->player2;
        } else {
            info->activePlayer = &info->player2;
            info->enemyPlayer = &info->player1;
        }
        printf("%s's turn\n", info->activePlayer->name);
        int legalMoves = numberOfLegalMoves(info);

        if (legalMoves == 0 && flagIsSet) {
            //End Game
            return false;
        } else if (legalMoves == 0 && !flagIsSet) {
            //turn++
            //set flag
            flagIsSet = true;
        } else {
            success = true;
        }
    } while (!success);

    return true;
}

int numberOfLegalMoves(GameInfo *info)
{
    Position checkPosition;
    int numberOfLegalMoves = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        checkPosition.x = i;
        for (int j = 0; j < BOARD_SIZE; j++) {
            checkPosition.y = j;
            //printf("CheckPos x: %d, y: %d\n", checkPosition.x, checkPosition.y);
            if (!isFieldTaken(&info->currentBoard, &checkPosition, true)) {
                if (isMoveLegal(info, &checkPosition, 0)) {
                    numberOfLegalMoves++;
                }
            }
        }
    }
    printf("%s has %d legal moves\n", info->activePlayer->name, numberOfLegalMoves);
    return numberOfLegalMoves;
}