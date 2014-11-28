#ifndef PLAYER_H
#define PLAYER_H
#include "Tile.h"
#include "GameController.h"
#include "EnumTypes.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>

class Player
{
public:
    ///Constructors and Destructors
    Player();
    ~Player();

    ///Getters and Setters
    //Getters
    int getSteps();
    //Setters
    void setSteps( int steps );
    //Increment
    void oneMoreStep();

    ///Methods
    //Takes key presses and adjusts the Player's velocity
    void handleEvent( SDL_Event& e, bool& exitFlag, Tile* tiles[] );

    //Moves the Player and check collision against tiles
    //void move( Tile *tiles[]);

    //Centers the camera over the Player
    void setCamera( SDL_Rect& camera );

    //Shows the Player on the screen
    void render( SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& gPlayerTexture );

    //gives us the box to pass around and check collision
    SDL_Rect getBox();

    //Box collision detector
    bool checkCollision( SDL_Rect a, SDL_Rect b );

    //Checks collision box against set of tiles
    bool touchesWall( SDL_Rect mBox, Tile* tiles[] );

    //Checks collision
  /*  int checkCollision( SDL_Rect a, SDL_Rect b );

    //Touches
    bool touchesWall( SDL_Rect box, Tile* tiles[] );*/
/*
    //Display Steps
    void displaySteps( SDL_Renderer* gRenderer );

    //Load font file
    bool loadFont( std::string fileName );
*/

private:
    int steps;
    TTF_Font* font;
    SDL_Color fontColor;

    //Collision box of the Player
    SDL_Rect mBox;
};

#endif // PLAYER_H
