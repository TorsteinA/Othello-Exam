//
// Created by torsteinalvern on 14/12/16.
//

#ifndef HOMEEXAM_UTILITIES_H
#define HOMEEXAM_UTILITIES_H


#include <stdio.h>
#include "board.h"


typedef struct Position {
    int x;
    int y;
} Position;


typedef struct Player
{
    char *name;
    Field field;
    bool ai;
}Player;


typedef struct GameInfo {
    Board currentBoard;
    Player player1;
    Player player2;
    Player *activePlayer;
    Player *enemyPlayer;
    FILE *fp;
    char *logName;
} GameInfo;


///
/// \param c: a char to convert
/// \return: corresponding int where a = 0, b = 1, etc.
int charToInt(char c);

///
/// \param info: Game info
/// \param inputPosition: The position the player/AI chose
/// \param x: Direction X
/// \param y: Direction Y
/// \param distance: Distance in XY direction from position
void flipTiles(GameInfo *info, Position *inputPosition, int x, int y, int distance);

///
/// \param info: Game info
/// \param position: Position on board to flip tile between black and white.
void flipTile(GameInfo *info, Position *position);

///
/// \param info: Game info
void findWinner(GameInfo *info);

///
/// \param info: Game info
/// \param round: which round it is in the game
/// \return Returns false if neither player has legal moves this turn, true otherwise.
bool setTurn(GameInfo *info, int *round);

///
/// \param info: Game info
/// \return: number of legal moves for the active player this round
int numberOfLegalMoves(GameInfo *info);


#endif //HOMEEXAM_UTILITIES_H
