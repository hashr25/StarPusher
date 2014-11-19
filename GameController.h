#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "EnumTypes.h"
#include "Tile.h"
#include "Player.h"
#include "Star.h"
#include "Level.h"

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

    //Main game loop
    void runGame();

    //Load game levels
    void loadLevels();

    std::vector<Level> getLevels();

private:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Scene textures
    LTexture gPlayerTexture;
    LTexture gTileTexture;
    SDL_Rect gTileClips[ TOTAL_TEXTURES ];

    //Levels
    std::vector<Level> gameLevels;
    int currentLevel;
};

#endif // GAMECONTROLLER_H
