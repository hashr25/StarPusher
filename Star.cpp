#include "Star.h"

/// //////////////////////////////////////////////////////////////////////////////
///Constructors
Star::Star()
{
    isAtGoal = false;
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

}

void Star::push( Direction directionToPush )
{
    switch ( directionToPush )
    {
    case NORTH:
        {
            setMapY( getMapY() - 1 );
            break;
        }
    case EAST:
        {
            setMapX( getMapX() + 1 );
            break;
        }
    case WEST:
        {
            setMapX( getMapX() - 1 );
            break;
        }
    case SOUTH:
        {
            setMapY( getMapY() + 1 );
            break;
        }
    }
}
