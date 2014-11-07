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
}

void Tile::setMapY( int mapY )
{
    this -> mapY = mapY;
}

void Tile::setType( TileType type )
{
    this -> type = type;
}

void Tile::setImage( SDL_Texture* image )
{
    this -> image = image;
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

    if( mapY != 0 )
    {
        cutRect.x = 0;
        cutRect.y = 25;
        cutRect.h = TILE_HEIGHT;
        cutRect.w = TILE_WIDTH;

        SDL_RenderCopy( renderer, image, &cutRect, &positionRect );
    }

    else
    {
        SDL_RenderCopy( renderer, image, NULL, &positionRect );
    }

    std::cout << "Printing grass at " << positionRect.x << ", " << positionRect.y << std::endl;
    std::cout << "Printing grass at " << mapX << ", " << mapY << std::endl;
}
