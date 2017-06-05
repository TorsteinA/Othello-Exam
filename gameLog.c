#include "gameLog.h"

void newLog(FILE *fp, char *logName)
{

    remove(logName);

    fp = fopen(logName, "w");
    if (fp == NULL)
    {
        printf("File Not Found!\n");
    } else
    {
        fprintf(fp, "\n\t\tOthello Log:\n\n\n");
    }
    fclose(fp);
}

void logMove(Position *inputPosition, Player *activePlayer, int round, FILE *fp, char *logName)
{

    fp = fopen(logName, "a");
    if (fp == NULL)
    {
        printf("File Not Found!\n");
    } else {
        fprintf(fp,"Round %d\n%s placed a tile on %c%d\n\n\n", round, activePlayer->name, inputPosition->x+49+'0', inputPosition->y+1); //Player *activePlayer,
    }
    fclose(fp);
}

void finishLog(char *playerName, int points, FILE *fp, char *logName)
{
    fp = fopen(logName, "a");
    if (fp == NULL)
    {
        printf("File Not Found!\n");
    } else if(points == 0)
    {
        fprintf(fp, "\n\n\t\tThe game finished with a draw!\n\n");
    } else
    {
        fprintf(fp,"\n\n\t\tThe Winner was %s with %d points!\n\n", playerName, points);
    }
    fclose(fp);
}

