#include "Player.h"

///Constructors and Destructors
Player::Player()
{
    steps = 0;
}

Player::Player( int newMapX, int newMapY, TileType newType, SDL_Texture* newImage)
{
    setMapX( newMapX );
    setMapY( newMapY );
    setType( newType );
    setImage( newImage );

    assert( getMapX() > 0 );
    assert( getMapY() > 0 );
    assert( newImage != NULL );
}

///Getters and Setters
//Getters
int Player::getSteps()
{
    return steps;
}

//Setters
void Player::setSteps( int steps )
{
    this -> steps = steps;
}

//Increment
void Player::oneMoreStep()
{
    steps++;
}

///Methods
Direction Player::getMove( bool &exitFlag )
{
    SDL_Event keyPress;
    Direction directionToMove;

    while( SDL_PollEvent( &keyPress ) != 0 )
    {
        if( keyPress.type == SDL_QUIT )
        {
            exitFlag = true;
        }

        else if( keyPress.type == SDL_KEYDOWN )
        {
            /**
            These methods are just to show movement for now.
            Error checking will be implemented when Map is created
            */

            if ( keyPress.key.keysym.sym == SDLK_DOWN )
            {
                ///Player moves North
                moveNorth();
                directionToMove = NORTH;
            }

            else if( keyPress.key.keysym.sym ==  SDLK_RIGHT )
            {
                ///Player moves East
                moveEast();
                directionToMove = EAST;
            }

            else if ( keyPress.key.keysym.sym == SDLK_UP )
            {
                ///Player moves South
                moveSouth();
                directionToMove = SOUTH;
            }

            else if( keyPress.key.keysym.sym == SDLK_LEFT )
            {
                ///Player moves West
                moveWest();
                directionToMove = WEST;
            }
        }
    }

    return directionToMove;
}

void Player::moveNorth()
{
    ///Error check based on the map size and environment
    setMapY( getMapY() + 1 );
    oneMoreStep();
}

void Player::moveEast()
{
    ///Error check based on the map size and environment
    setMapX( getMapX() + 1 );
    oneMoreStep();
}

void Player::moveSouth()
{
    if( (getMapY() - 1) < 0 )
    {
        setMapY( 0 );
    }

    else
    {
        setMapY( getMapY() - 1 );
        oneMoreStep();
    }
}

void Player::moveWest()
{
    if( (getMapX()-1) < 0 )
    {
        setMapX( 0 );
    }

    else
    {
        setMapX( getMapX() - 1 );
        oneMoreStep();
    }
}
