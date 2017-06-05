#ifndef __GAMELOG_H__
#define __GAMELOG_H__

#include <stdio.h>
#include "board.h"
#include "utilities.h"

/// Removes old file with same name and starts a new log
/// \param fp: File pointer
/// \param logName: name of log file
void newLog(FILE *fp, char *logName);

/// Logs moves while game is being played
/// \param inputPosition: Position the player/AI chose
/// \param activePlayer: Whose turn it is
/// \param round: Which round it is
/// \param fp: File pointer
/// \param logName: Name of log
void logMove(Position *inputPosition, Player *activePlayer, int round, FILE *fp, char *logName);

/// Ends log file by printing the end result to the file.
/// \param playerName: Name of winning player
/// \param points: How many points winning player had
/// \param fp: File pointer
/// \param logName: Name of log file
void finishLog(char *playerName, int points, FILE *fp, char *logName);


#endif //__GAMELOG_H__
