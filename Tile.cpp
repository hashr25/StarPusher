#include "Tile.h"

/// //////////////////////////////////////////////////////////////////////////////
///Constructors and Destructors
Tile::Tile()
{
    image = NULL;
}

Tile::Tile( int newMapX, int newMapY, TileType newType, SDL_Texture* newImage ) :
    mapX(newMapX), mapY(newMapY), type(newType), image(newImage)
{
    assert( mapX >= 0 );
    assert( mapY >= 0 );
}

Tile::~Tile()
{
    image = NULL;
}

/// /////////////////////////////////////////////////////////////////////////////
///Getters and Setters
//Getters
int Tile::getMapX()
{
    return mapX;
}

int Tile::getMapY()
{
    return mapY;
}

TileType Tile::getType()
{
    return type;
}

SDL_Texture* Tile::getImage()
{
    return image;
}

//Setters
void Tile::setMapX( int mapX )
{
    this -> mapX = mapX;
    assert( mapX >= 0 );
}

void Tile::setMapY( int mapY )
{
    this -> mapY = mapY;
    assert( mapY >= 0 );
}

void Tile::setType( TileType type )
{
    this -> type = type;
}

void Tile::setImage( SDL_Texture* image )
{
    this -> image = image;

    //Testing to make sure there is an image
    assert( image != NULL );
}

/// ///////////////////////////////////////////////////////////////////
///Methods

void Tile::displayTile( SDL_Renderer* renderer )
{
    SDL_Rect positionRect;
    SDL_Rect cutRect;

    positionRect.x = mapX * TILE_WIDTH;
    positionRect.y = mapY * TILE_FLOOR_HEIGHT;
    positionRect.h = TILE_HEIGHT;
    positionRect.w = TILE_WIDTH;

    assert( positionRect.x >= 0 );
    assert( positionRect.y >= 0 );

    SDL_RenderCopy( renderer, image, NULL, &positionRect );
}
