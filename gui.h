//
// Created by torsteinalvern on 08/12/16.
//
#ifndef _GUI_H
#define _GUI_H

#define WINDOW_WIDTH (1000)
#define WINDOW_HEIGHT (600)
#define FIELDS_START_POS_X (325)
#define FIELDS_START_POS_Y (183)
#define FIELD_SIZE_X (40)
#define FIELD_SIZE_Y (40)

#include "SDL2/SDL.h"
#include "board.h"
#include "checks.h"


typedef struct GuiInfo{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *backgroundTexture;
    SDL_Texture *blackTile;
    SDL_Texture *whiteTile;
    SDL_Rect blackTileDest;
    SDL_Rect whiteTileDest;
}GuiInfo;


/// Initializes the GUI
/// \param info: Game info
void initializeGUI(GameInfo *info);

/// Places a tile
/// \param color: What color tile to place
/// \param position: Where to place the tile
void placeTile(Field color, Position *position);

/// Clears and rerenders the GUI for every change that occurs
/// \param info: Game info
void renderGUI(GameInfo *info);

/// Closes resources and exits GUI
void exitGUI();

/// Waits for player to make a move
/// \return: Tile position where player clicked on board
Position runGuiPlayerEvents();

/// Method that runs when player presses the mouse button
/// \param x: X position of mouse click
/// \param y: Y position of mouse click
/// \return: Tile position where player clicked on board
Position OnMouse(Sint32 x, Sint32 y);

/// Keeps window active when only AI's play, and allows user the exit window with X button in window corner.
void runGuiAIEvents();


#endif //_GUI_H
