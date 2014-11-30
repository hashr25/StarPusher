#include "Star.h"

/// //////////////////////////////////////////////////////////////////////////////
///Constructors
Star::Star()
{
    isAtGoal = false;
}

Star::Star( int x, int y )
{
    this -> x = x;
    this -> y = y;
}

/// /////////////////////////////////////////////////////////////////////////////
///Getters and Setters
//Getters
bool Star::getIsAtGoal() const
{
    return isAtGoal;
}

//Setters
void Star::setIsAtGoal(bool isAtGoal)
{
    this -> isAtGoal = isAtGoal;
}

bool Star::isBlocked( Direction directionToCheckS )
{
    bool isBlocked = false;


    return isBlocked;
}

void Star::push( Direction directionToPush )
{
    switch ( directionToPush )
    {
    case NORTH:
        {
            //setMapY( getMapY() - 1 );
            break;
        }
    case EAST:
        {
            //setMapX( getMapX() + 1 );
            break;
        }
    case WEST:
        {
            //setMapX( getMapX() - 1 );
            break;
        }
    case SOUTH:
        {
            //setMapY( getMapY() + 1 );
            break;
        }
    }
}

bool Star::checkCollision( SDL_Rect a, SDL_Rect b )
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

void Star::render( SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect gTileClips[ TOTAL_TYPES ], LTexture& gTileTexture )
{
    SDL_Rect starBox;
    starBox.x = x * TILE_WIDTH;
    starBox.y = y * TILE_FLOOR_HEIGHT;
    //If the tile is on screen
    if( checkCollision( camera, starBox ) )
    {
        //Show the tile
        gTileTexture.render( starBox.x - camera.x, starBox.y - camera.y, &gTileClips[ STAR ], gRenderer );
    }
}
