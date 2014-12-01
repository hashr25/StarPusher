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
<<<<<<< HEAD
    bool loadMedia( SDL_Renderer* gRenderer );
=======
    bool loadMedia( Tile* tiles[], SDL_Renderer* gRenderer );
>>>>>>> origin/CharlotteRose
    bool loadFont( std::string fileName );

    //Frees media and shuts down SDL
    void close();

    //Box collision detector
    bool checkCollision( SDL_Rect a, SDL_Rect b );

    //Checks collision box against set of tiles
    bool touchesWall( SDL_Rect box, Tile* tiles[] );

    //Sets tiles from tile map
    bool setTiles( Tile *tiles[] );

    //Main game loop
    void runGame();

    //Load game levels
<<<<<<< HEAD
    void loadLevels();

    //Returns levels
    Level* getLevels();

    //Changes levels
    void changeLevels( SDL_Event& e );
=======
    //void loadLevels();

    //Returns levels
    //std::vector<Level> getLevels();
>>>>>>> origin/CharlotteRose

    //Displays level number on screen
    void displayLevelNumber();

    //Camera Motion
    void moveCamera( SDL_Event& e );
    void changeCamera();
    int cameraVelX;
    int cameraVelY;

<<<<<<< HEAD
    //Render level
    void renderLevel();
    void nextLevel();
    void previousLevel();
    void resetLevel();
    void centerCamera();
=======
>>>>>>> origin/CharlotteRose

private:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Camera
    SDL_Rect camera;

    //Scene textures
    LTexture gPlayerTexture;
    LTexture gTileTexture;
<<<<<<< HEAD
    SDL_Rect gTileClips[ TOTAL_TYPES ];
=======
    SDL_Rect gTileClips[ TOTAL_TEXTURES ];
>>>>>>> origin/CharlotteRose

    //Levels
    TTF_Font* font;
    SDL_Color fontColor;
<<<<<<< HEAD
    Level gameLevels[ TOTAL_LEVELS ];
    int currentLevel;

    Player player;
    std::vector<Star> gameStars;
=======
    std::vector<Level> gameLevels;
    int currentLevel;
>>>>>>> origin/CharlotteRose
};

#endif // GAMECONTROLLER_H
