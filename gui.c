#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "gui.h"

void createWindow(GuiInfo *guiInfo);
void createRenderer(GuiInfo *guiInfo);
void createSurface(GuiInfo *guiInfo);
void createTexture(GuiInfo *guiInfo);
void createTiles(GuiInfo *guiInfo);


GuiInfo guiInfo;

void initializeGUI(GameInfo *info)
{
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) !=0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }
    //printf("Initialization successfull!\n");

    createWindow(&guiInfo);
    createRenderer(&guiInfo);
    createSurface(&guiInfo);
    createTexture(&guiInfo);
    createTiles(&guiInfo);

    //Clear window
    SDL_RenderClear(guiInfo.renderer);

    //Draw the image to the window
    SDL_RenderCopy(guiInfo.renderer, guiInfo.backgroundTexture, NULL, NULL);

    //Place initial tiles
    Position initPos;
    initPos.x = 3;
    initPos.y = 3;
    placeTile(BLACK, &initPos);
    initPos.x +=1;
    placeTile(WHITE, &initPos);
    initPos.y +=1;
    placeTile(BLACK, &initPos);
    initPos.x -=1;
    placeTile(WHITE, &initPos);


    //Render changes
    renderGUI(info);

    //scanf("Wob wob");   //Stops the output from racing forward until I type something. Only temporary
    //SDL_Delay(500);
}

void createWindow(GuiInfo *guiInfo)
{
    guiInfo->window= SDL_CreateWindow("Othello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!guiInfo->window)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        exitGUI();
    }
}

void createRenderer(GuiInfo *guiInfo)
{
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    guiInfo->renderer = SDL_CreateRenderer(guiInfo->window, -1, render_flags);
    if(!guiInfo->renderer)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        exitGUI();
    }
}

void createSurface(GuiInfo *guiInfo)
{
    guiInfo->surface = IMG_Load("Resources/Othello.jpg");
    if (!guiInfo->surface)
    {
        printf("Error creating surface");
        exitGUI();
    }
}

void createTexture(GuiInfo *guiInfo)
{
    guiInfo->backgroundTexture = SDL_CreateTextureFromSurface(guiInfo->renderer, guiInfo->surface);
    SDL_FreeSurface(guiInfo->surface);
    if(!guiInfo->backgroundTexture)
    {
        printf("Error creating texture: %s\n", SDL_GetError());
        exitGUI();
    }

}

void createTiles(GuiInfo *guiInfo)
{
    SDL_Surface *blackTileSurface = IMG_Load("Resources/OthelloBlackTile.png");
    SDL_Surface *whiteTileSurface = IMG_Load("Resources/OthelloWhiteTile.png");
    if(!blackTileSurface || !whiteTileSurface)
    {
        printf("Error creating tile surfaces\n");
        exitGUI();
    }

    guiInfo->blackTile = SDL_CreateTextureFromSurface(guiInfo->renderer, blackTileSurface);
    guiInfo->whiteTile = SDL_CreateTextureFromSurface(guiInfo->renderer, whiteTileSurface);
    SDL_FreeSurface(blackTileSurface);
    SDL_FreeSurface(whiteTileSurface);
    if(!guiInfo->blackTile || !guiInfo->whiteTile)
    {
        printf("Error creating tile textures\n");
        exitGUI();
    }
}

void renderGUI(GameInfo *info)
{
    Position checkPosition;

    SDL_RenderClear(guiInfo.renderer);
    SDL_RenderCopy(guiInfo.renderer, guiInfo.backgroundTexture, NULL, NULL);

    for(checkPosition.x = 0; checkPosition.x < BOARD_SIZE; checkPosition.x++){
        for(checkPosition.y = 0; checkPosition.y < BOARD_SIZE; checkPosition.y++){
            if(info->currentBoard.fields[checkPosition.x][checkPosition.y] == WHITE){
                placeTile(WHITE, &checkPosition);
            } else if (info->currentBoard.fields[checkPosition.x][checkPosition.y] == BLACK){
                placeTile(BLACK, &checkPosition);
            }
        }
    }
    SDL_RenderPresent(guiInfo.renderer);
    SDL_Delay(200);
}

void placeTile(Field color, Position *position)
{
    if (color == WHITE)
    {
        SDL_QueryTexture(guiInfo.whiteTile, NULL, NULL, &guiInfo.whiteTileDest.w, &guiInfo.whiteTileDest.h);
        guiInfo.whiteTileDest.x = FIELDS_START_POS_X + FIELD_SIZE_X * position->x;
        guiInfo.whiteTileDest.y = FIELDS_START_POS_Y + FIELD_SIZE_Y * position->y;
        SDL_RenderCopy(guiInfo.renderer, guiInfo.whiteTile, NULL, &guiInfo.whiteTileDest);

    } else if (color == BLACK)
    {
        SDL_QueryTexture(guiInfo.blackTile, NULL, NULL, &guiInfo.blackTileDest.w, &guiInfo.blackTileDest.h);
        guiInfo.blackTileDest.x = FIELDS_START_POS_X + FIELD_SIZE_X * position->x;
        guiInfo.blackTileDest.y = FIELDS_START_POS_Y + FIELD_SIZE_Y * position->y;
        SDL_RenderCopy(guiInfo.renderer, guiInfo.blackTile, NULL, &guiInfo.blackTileDest);

    } else
    {
        //Error
        printf("Cannot place tile as it's neither black nor white\n");
    }
}

Position runGuiPlayerEvents()
{
    bool requestedClose = false;
    printf("Running Gui Player Events function\n");
    SDL_Event event;
    Position guiInputPos;
    guiInputPos.x = -1;
    guiInputPos.y = -1;

    while (!requestedClose){
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exitGUI();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    guiInputPos = OnMouse(event.button.x, event.button.y);
                    if (guiInputPos.x != -1 && guiInputPos.y != -1) {
                        return guiInputPos;
                    }
                    break;
//                default:
//                    printf("Default Switch from GUI events\n");
            }
        }
        if(guiInputPos.x != -1 && guiInputPos.y != -1){
            requestedClose = true;
        }
    }
    return guiInputPos;
}

void runGuiAIEvents()
{
    bool requestedClose = false;
    printf("Running Gui AI Events function\n");
    SDL_Event event;

    while (!requestedClose){
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exitGUI();
                    break;
//            default:
//                printf("Default Switch from GUI events\n");
            }
        }
        requestedClose = true;
    }
}

Position OnMouse(Sint32 x, Sint32 y)
{
    Position guiInputPos;
    guiInputPos.x = -1;
    guiInputPos.y = -1;
    if(
            x >= FIELDS_START_POS_X &&
            x <= FIELDS_START_POS_X + (FIELD_SIZE_X * BOARD_SIZE) &&
            y >= FIELDS_START_POS_Y &&
            y <= FIELDS_START_POS_Y + (FIELD_SIZE_Y * BOARD_SIZE)
            )
    {
        //printf("Mouse press is inside borders\n");
        int xVal = (x - FIELDS_START_POS_X) / FIELD_SIZE_X;
        int yVal = (y - FIELDS_START_POS_Y) / FIELD_SIZE_Y;

        for(int i = 0; i <= BOARD_SIZE; i++){
            for(int j = 0; j <= BOARD_SIZE; j++){
                if (i == xVal && j == yVal){
                    printf("Mouse clicked on %c%d\n", xVal + 49 + '0', yVal+1); //Converts int x to char on board, and y to value on board
                    guiInputPos.x = xVal;
                    guiInputPos.y = yVal;
                    return guiInputPos;
                }
            }
        }
    }
    return guiInputPos;
}

void exitGUI()
{
    //SDL_Delay(5000);
    SDL_DestroyRenderer(guiInfo.renderer);
    SDL_DestroyWindow(guiInfo.window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
    printf("Quit GUI successfully\n");
}
