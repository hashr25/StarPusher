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
#include "Player.h"
#include "Tile.h"
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
    bool loadMedia( SDL_Renderer* gRenderer );
    bool loadFont( std::string fileName );

    //Frees media and shuts down SDL
    void close();

    //Box collision detector
    bool checkCollision( SDL_Rect a, SDL_Rect b );

    //Checks collision box against set of tiles
    bool touchesWall( SDL_Rect box, int x, int y );
    bool starTouchesWall(int x, int y);
    bool starTouchesStar(int x, int y);
    int touchesStar( int x, int y );


    //Sets tiles from tile map
    bool setTiles( Tile *tiles[] );

    //Main game loop
    void runGame();

    //Load game levels
    void loadLevels();

    //Returns levels
    Level* getLevels();

    //Changes levels
    void changeLevels( SDL_Event& e );

    //Displays level number on screen
    void displayLevelNumber();

    //Camera Motion
    void moveCamera( SDL_Event& e );
    void changeCamera();
    int cameraVelX;
    int cameraVelY;

    //Render level
    void renderLevel();
    void nextLevel();
    void previousLevel();
    void resetLevel();
    void centerCamera();

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
    SDL_Rect gTileClips[ TOTAL_TYPES ];

    //Levels
    TTF_Font* font;
    SDL_Color fontColor;
    Level gameLevels[ TOTAL_LEVELS ];
    int currentLevel;

    Player player;
    std::vector<Star> gameStars;
};

#endif // GAMECONTROLLER_H
