//
// Created by torsteinalvern on 14/12/16.
//

#ifndef HOMEEXAM_INPUT_H
#define HOMEEXAM_INPUT_H

#include "board.h"

/// Prompts for how many players will be playing this game
/// \return number of players playing this game
int getNumberOfPlayers();

/// Get a move from the player through console.
/// \param inputPosition: Position values to update with user input
void getUserInput(Position *inputPosition);

/// Get a move from the AI
/// \param inputPosition: Position values to update with AI input
void getAIInput(Position *inputPosition);

/// Get name of player in text from console
/// \param player: Player's name to set
void getUserNameInput(Player *player);



#endif //HOMEEXAM_INPUT_H
