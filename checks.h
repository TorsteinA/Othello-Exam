#ifndef CHECKS_H
#define CHECKS_H

#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "utilities.h"

///
/// \param board: The game board
/// \param inputPosition: The position the player/AI chose
/// \param x: Direction X
/// \param y: Direction Y
/// \param distance: distance in direction XY from position
/// \return: True if field is empty, false otherwise
bool isEmptyField(Board *board, Position *inputPosition, int x, int y, int distance);

///
/// \param board: The game board
/// \param inputPosition: The position the player/AI chose
/// \param oppositeField: The enemy player's color
/// \param x: Direction X
/// \param y: Direction Y
/// \param distance: distance in direction XY from position
/// \return: True if field is same as oppositeField, false otherwise
bool isEnemyField(Board *board, Position *inputPosition, Field *oppositeField, int x, int y, int distance);

///
/// \param board: The game board
/// \param inputPosition: The position the player/AI chose
/// \param activeField: The active player's color
/// \param x: Direction X
/// \param y: Direction Y
/// \param distance: distance in direction XY from position
/// \return: True if field is same as activeField
bool isFriendlyField(Board *board, Position *inputPosition, Field *activeField, int x, int y, int distance);

///
/// \param board: The game board
/// \param inputPosition: The position the player/AI chose
/// \param justChecking: Flag for print statement
/// \return: True if field is taken, false otherwise
bool isFieldTaken(Board *board, Position *inputPosition, bool justChecking);

///
/// \param inputPosition: The position the player/AI chose
/// \return: True if move is within border, false otherwise
bool isUserInputLegal(Position *inputPosition);

///
/// \param info: GameInfo
/// \param inputPosition: The position the player/AI chose
/// \param mode: 0: Search for legal moves. 1: Check if input is legal, 2: Flipping tiles
/// \return: True if move is legal, false otherwise
bool isMoveLegal(GameInfo *info, Position *inputPosition, int mode);

///
/// \param position: Position to check if is inside border
/// \param x: Direction X from position
/// \param y: Direction Y from position
/// \param distance: distance in direction XY from position
/// \return: True if combined position inside border, false otherwise
bool isInsideBorder(Position *position, int x, int y, int distance);

///
/// \param board: The game board
/// \return: True if BOARD_SIZE² spots on the board is not empty, false otherwise
bool isBoardFull(Board *board);

#endif //CHECKS_H