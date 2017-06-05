//
// Created by torsteinalvern on 14/12/16.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "checks.h"
#include "gui.h"


int getNumberOfPlayers()
{
    int numberOfPlayers = -1;
    int scan;
    do {
        printf("How many players? ('0' to watch AI's play. '1' to play against AI, '2' to play against a friend)\n");
        scan = scanf("%d", &numberOfPlayers);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    } while ((numberOfPlayers != 0 && numberOfPlayers != 1 && numberOfPlayers != 2) || scan != 1);

    return numberOfPlayers;
}

void getUserNameInput(Player *player)
{

    int maxNameLength = 16;
    bool success = false;

    do {
        printf("Player, what's your name? (Max %d characters)\n", maxNameLength - 1);
        if (fgets(player->name, maxNameLength, stdin) != NULL) {
            success = true;
        }
        if (strlen(player->name) != 0) player->name[strlen(player->name) - 1] = '\0';
    } while (!success);

    //TODO Fix bug 'overflow for long names or double enter press for short names'
    int ch;
    while ((strlen(player->name) >= 15) && (ch = getchar()) != '\n' && ch != EOF); //(strlen(player->name) >= 15) && //Adding or removing this creates the first or second bug. They don't co-exist

    printf("Welcome to the game %s!\n", player->name);
}

void getUserInput(Position *inputPosition)
{
    char x;
    do {
        printf("Input your coordinates here: (example: c2 )\n> ");
        scanf(" %c%d", &x, &inputPosition->y);

        printf("Chosen tile is x: %c, y: %d\n", x, inputPosition->y);
        inputPosition->x = charToInt(x);
        inputPosition->y--;
        printf("Board position: x: %d, y: %d\n", inputPosition->x, inputPosition->y);

    } while (!isUserInputLegal(inputPosition));
}

void getAIInput(Position *inputPosition)
{
//TODO improve AI (Use greedy algorithm? (with corners worth 10, and tiles next to corners worth -5))
//If greedy algorithm is too much, make AI only choose between legal moves from an array (So basically the same as now, but optimized a bit)


    //Dumb AI. Returns random position on board. Can get tedious sometimes.
    inputPosition->x = rand() % BOARD_SIZE;
    inputPosition->y = rand() % BOARD_SIZE;


    //This is to keep the GUI window active when no players use events (Game with 0 human players)
    runGuiAIEvents();





    ///Plan here was to cycle through all tiles,
    /// check how many tiles they flip,
    /// and choose the one that gives more points.
    /// (Bonus: Make corner tiles worth 10x, and the ones next to the corners -5x)
//    Position chandidatePosition;
//    Position checkPosition;
//    int highestNumberOfFlips = 0;
//    int checkedNumberOfFlips = 0;
//
//    for(int i = 0; i <= BOARD_SIZE-1; i++){
//        checkPosition.x = i;
//        for(int j = 0; j <= BOARD_SIZE-1; j++){
//            checkPosition.y = j;
//            if(!isFieldTaken(&currentBoard, &checkPosition, true)){ //isMoveLegal(&currentBoard, &checkPosition, activePlayer, enemyPlayer, 0)){
//
//                inputPosition->x = checkPosition.x;
//                inputPosition->y = checkPosition.y;
//                printf("Board position: x: %c, y: %d\n", inputPosition->x +49 +'0', inputPosition->y+1);
//
//            }
//            if(isMoveLegal(&currentBoard, &checkPosition, activePlayer, enemyPlayer, 0)){
//                checkedNumberOfFlips++;
//            }
//        }
//    }

}
