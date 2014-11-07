#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <cassert>
#include <iostream>

#include "EnumTypes.h"

/* Used for Testing Purposes */
const int TILE_HEIGHT = 85;
const int TILE_WIDTH = 50;
const int TILE_FLOOR_HEIGHT = 40;

class Tile
{
public:
    ///Constructors and Destructors
    Tile();
    Tile( int mapX, int mapY, TileType type, SDL_Texture* image );
    ~Tile();

    ///Getters and Setters
    //Getters
    int getMapX();
    int getMapY();
    TileType getType();
    SDL_Texture* getImage();
    //Setters
    void setMapX( int mapX );
    void setMapY( int mapY );
    void setType( TileType type );
    void setImage( SDL_Texture* image );

    ///Methods
    void displayTile( SDL_Renderer* renderer );

private:
    int mapX;
    int mapY;
    TileType type;
    SDL_Texture* image;
};

#endif // TILE_H
