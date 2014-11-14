#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"
#include "EnumTypes.h"
#include <SDL.h>

class Player
{
public:
    ///Constructors and Destructors
    Player();

    ///Getters and Setters
    //Getters
    int getSteps();
    //Setters
    void setSteps( int steps );
    //Increment
    void oneMoreStep();

    ///Methods
    //Takes key presses and adjusts the Player's velocity
    void handleEvent( SDL_Event& e, bool& exitFlag );

    //Moves the Player and check collision against tiles
    void move( Tile *tiles[] );

    //Centers the camera over the Player
    void setCamera( SDL_Rect& camera );

    //Shows the Player on the screen
    void render( SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& gPlayerTexture );

    //Checks collision
    bool checkCollision( SDL_Rect a, SDL_Rect b );

    //Touches
    bool touchesWall( SDL_Rect box, Tile* tiles[] );

private:
    int steps;

    //Collision box of the Player
    SDL_Rect mBox;

    //The velocity of the Player
    int mVelX, mVelY;
};

#endif // PLAYER_H
