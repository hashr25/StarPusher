#include "Star.h"

/// //////////////////////////////////////////////////////////////////////////////
///Constructors
Star::Star()
{
    isAtGoal = false;

    mBox.x = 0;
    mBox.y = 0;
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

}

Star::Star( int x, int y )
{
    isAtGoal = false;

    mBox.x = x;
    mBox.y = y;
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
}

/// /////////////////////////////////////////////////////////////////////////////
///Getters and Setters
//Getters
bool Star::getIsAtGoal() const
{
    return isAtGoal;
}

SDL_Rect Star::getStarRect() const
{
    SDL_Rect result;

    result.x = mBox.x;
    result.y = mBox.y;
    result.w = mBox.x + mBox.w;
    result.h = mBox.y + mBox.h;

    return result;
}

//Setters
void Star::setIsAtGoal(bool isAtGoal)
{
    this -> isAtGoal = isAtGoal;
}

void Star::setTopLeft( int x, int y )
{
    this -> mBox.x = x;
    this -> mBox.y = y;
}

bool Star::isBlocked( Direction directionToCheck, Tile *tiles[] )
{
    bool isBlocked = false;

    switch ( directionToCheck )
    {
    case NORTH:
        {

            break;
        }
    case SOUTH:
        {

            break;
        }
    case EAST:
        {

            break;
        }
    case WESTS:
        {

            break;
        }
    }

    return isBlocked;
}

void Star::push( Direction directionToPush )
{
    switch ( directionToPush )
    {
    case NORTH:
        {
            //setMapY( getMapY() - 1 );
            this -> mBox.y -= TILE_FLOOR_HEIGHT;
            break;
        }
    case EAST:
        {
            //setMapX( getMapX() + 1 );
            this -> mBox.x += TILE_WIDTH;
            break;
        }
    case WEST:
        {
            //setMapX( getMapX() - 1 );
            this -> mBox.x -= TILE_WIDTH;
            break;
        }
    case SOUTH:
        {
            //setMapY( getMapY() + 1 );
            this -> mBox.y += TILE_FLOOR_HEIGHT;
            break;
        }
    }
}
