#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"
#include <SDL.h>

class Player : public Tile
{
public:
    ///Constructors and Destructors
    Player();
    Player( int newMapX, int newMapY, TileType newType, SDL_Texture* newImage );

    ///Getters and Setters
    //Getters
    int getSteps();
    //Setters
    void setSteps( int steps );
    //Increment
    void oneMoreStep();

    ///Methods
    Direction getMove( bool &exitFlag );

    void moveNorth();
    void moveEast();
    void moveSouth();
    void moveWest();

private:
    int steps;
};

#endif // PLAYER_H
