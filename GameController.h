#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>

#include "EnumTypes.h"
#include "Tile.h"
#include "Player.h"
#include "Star.h"

class GameController
{
public:
    //Constructor
    GameController();

    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedia( Tile* tiles[], SDL_Renderer* gRenderer );

    //Frees media and shuts down SDL
    void close( Tile* tiles[] );

    //Box collision detector
    bool checkCollision( SDL_Rect a, SDL_Rect b );

    //Checks collision box against set of tiles
    bool touchesWall( SDL_Rect box, Tile* tiles[] );

    //Sets tiles from tile map
    bool setTiles( Tile *tiles[] );

private:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Scene textures
    LTexture gPlayerTexture;
    LTexture gTileTexture;
    SDL_Rect gTileClips[ TOTAL_TEXTURES ];
};

#endif // GAMECONTROLLER_H
