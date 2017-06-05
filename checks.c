#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "checks.h"

bool isEmptyField(Board *board, Position *inputPosition, int x, int y, int distance)
{
    Position checkPosition = *inputPosition;
    checkPosition.x = checkPosition.x + (x * distance);
    checkPosition.y = checkPosition.y + (y * distance);

    if(board->fields[checkPosition.x][checkPosition.y] == EMPTY)
    {
        return true;
    } else
    {
        return false;
    }
}

bool isEnemyField(Board *board, Position *inputPosition, Field *oppositeField, int x, int y, int distance)
{
    Position checkPosition = *inputPosition;
    checkPosition.x = checkPosition.x + (x * distance);
    checkPosition.y = checkPosition.y + (y * distance);

    if(board->fields[checkPosition.x][checkPosition.y] == *oppositeField)
    {
        return true;
    } else
    {
        return false;
    }
}

bool isFriendlyField(Board *board, Position *inputPosition, Field *activeField, int x, int y, int distance)
{
    Position checkPosition = *inputPosition;
    checkPosition.x = checkPosition.x + (x * distance);
    checkPosition.y = checkPosition.y + (y * distance);

    if(board->fields[checkPosition.x][checkPosition.y] == *activeField)
    {
        return true;
    } else
    {
        return false;
    }
}

bool isFieldTaken(Board *board, Position *inputPosition, bool justChecking)
{
    if(board->fields[inputPosition->x][inputPosition->y] == EMPTY) {
        return false;
    } else {

        if (!justChecking)
            printf("That position is already taken\nPlease try again\n");

        return true;
    }
}

bool isUserInputLegal(Position *inputPosition)
{
    if(inputPosition->x < 0 || inputPosition->x >=8)
    {
        printf("Choose a valid letter\nPlease try again\n");
        return false;
    }
    if(inputPosition->y < 0 || inputPosition->y >=8)
    {
        printf("Choose a valid number\nPlease try again\n");
        return false;
    }

    return true;
}

bool isInsideBorder(Position *position, int x, int y, int distance)
{
    if(position->x + (x * distance) >= BOARD_SIZE || position->x + (x * distance) < 0) return false;
    if(position->y + (y * distance) >= BOARD_SIZE || position->y + (y * distance) < 0) return false;

    return true;
}

bool isMoveLegal(GameInfo *info, Position *inputPosition, int mode)
{
    Field enemyField = info->enemyPlayer->field;
    int distance = 0;
    bool legal = false;

    for(int x = - 1; x < 2; x++)
    {
        for(int y = - 1; y < 2; y++)
        {
            distance = 1;
            if(!isInsideBorder(inputPosition, x, y, distance))
            {
                //printf("Checked area outside border\n");
            }else if(isEmptyField(&info->currentBoard, inputPosition, x, y, distance))
            {
                //printf("Found empty tile\n");
            }else
            {
                while(isEnemyField(&info->currentBoard, inputPosition, &enemyField, x, y, distance))
                {
                    distance++;
                    if(distance > BOARD_SIZE) break;
                }
                if (distance >= 2)
                {
                    if(!isInsideBorder(inputPosition, x, y, distance)){
                        //printf("Checked area outside borders");
                    }else if(isEmptyField(&info->currentBoard, inputPosition, x, y, distance))
                    {
                        //printf("Found empty tile after enemy tile\n");
                    }else if (isFriendlyField(&info->currentBoard, inputPosition, &info->activePlayer->field, x, y, distance)){
                        //printf("Found friendly tile after enemy Tile\n");
                        legal = true;
                        if(mode == 2){
                            flipTiles(info, inputPosition, x, y, distance);
                        }
                    }
                }
            }
        }
    }

    if(legal)
    {
        if(mode == 0){
            printf("Legal position: %c%d\n", inputPosition->x +49 + '0', inputPosition->y + 1);  //Converts X to char and Y to values shown on table.
        }
        return true;
    } else {
        if(mode == 1)
            printf("That's an illegal move! Please try again\n");

        return false;
    }
}

bool isBoardFull(Board *board)
{
    Position checkPosition;
    int takenFields = 0;
    for (int i = 0; i <= BOARD_SIZE - 1; i++) {
        checkPosition.x = i;
        for (int j = 0; j <= BOARD_SIZE - 1; j++) {
            checkPosition.y = j;
            if (isFieldTaken(board, &checkPosition, true))
                takenFields++;
        }
    }
    if (takenFields >= BOARD_SIZE*BOARD_SIZE)
        return true;

    return false;
}
