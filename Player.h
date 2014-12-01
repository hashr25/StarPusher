#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"
#include "EnumTypes.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <vector>

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
    //Set Position
    void setPosition( int xPosition, int yPosition );

    ///Methods
    //Takes key presses and adjusts the Player's velocity
    void handleEvent( SDL_Event& e, bool& exitFlag, std::vector<Tile*> tiles );

    //Moves the Player and check collision against tiles
    //void move( Tile *tiles[], bool(*f)(SDL_Rect a, SDL_Rect b ) );
    //void move( Tile *tiles[]);
    //Centers the camera over the Player
    void setCamera( SDL_Rect& camera );

    //Shows the Player on the screen
    void render( SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& gPlayerTexture );

    //gives us the box to pass around an check collision
    SDL_Rect getBox();

    void setX(int newX);
    void setY(int newY);

    //Checks collision
    int checkCollision( SDL_Rect a, SDL_Rect b );

    //Touches
    bool touchesWall( SDL_Rect box, std::vector<Tile*> tiles );

    //Display Steps
    void displaySteps( SDL_Renderer* gRenderer );

    //Load font file
    bool loadFont( std::string fileName );

private:
    int steps;
    TTF_Font* font;
    SDL_Color fontColor;

    //Collision box of the Player
    SDL_Rect mBox;
};

#endif // PLAYER_H
