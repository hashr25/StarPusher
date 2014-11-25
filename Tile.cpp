#include "Tile.h"

Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    pBox.x = x;
    pBox.y = y;

    //Set the collision box
    pBox.w = TILE_WIDTH;
    pBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}

void Tile::render( SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect gTileClips[ TOTAL_TEXTURES ], LTexture& gTileTexture )
{
    //If the tile is on screen
    if( checkCollision( camera, pBox ) )
    {
        //Show the tile
        gTileTexture.render( pBox.x - camera.x, pBox.y - camera.y, &gTileClips[ mType ], gRenderer );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return pBox;
}

bool Tile::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
