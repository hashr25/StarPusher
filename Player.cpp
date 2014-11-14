#include "Player.h"

///Constructors and Destructors
Player::Player()
{
    steps = 0;

    //Initialize the collision box
    mBox.x = 0;
    mBox.y = 0;
	mBox.w = PLAYER_WIDTH;
	mBox.h = PLAYER_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
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
void Player::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mBox.y -= TILE_FLOOR_HEIGHT; break;
            case SDLK_DOWN: mBox.y += TILE_FLOOR_HEIGHT; break;
            case SDLK_LEFT: mBox.x -= TILE_WIDTH; break;
            case SDLK_RIGHT: mBox.x += TILE_WIDTH; break;
        }
    }
}

void Player::move( Tile *tiles[] )
{
    //Move the dot left or right
    mBox.x += mVelX;

    //If the dot went too far to the left or right or touched a wall
    if( ( mBox.x < 0 ) || ( mBox.x + PLAYER_WIDTH > LEVEL_WIDTH ) )
    {
        //move back
        mBox.x -= mVelX;
    }

    //Move the dot up or down
    mBox.y += mVelY;

    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || ( mBox.y + PLAYER_HEIGHT > LEVEL_HEIGHT ) )
    {
        //move back
        mBox.y -= mVelY;
    }
}

void Player::setCamera( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox.x + PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 - LEVEL_WIDTH)
	{
		camera.x = 0;
	}
	if( camera.y < 0 - LEVEL_HEIGHT )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH /*- camera.w*/ )
	{
		camera.x = LEVEL_WIDTH /*- camera.w*/;
	}
	if( camera.y > LEVEL_HEIGHT /*- camera.h*/ )
	{
		camera.y = LEVEL_HEIGHT /*- camera.h*/;
	}
}

void Player::render( SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& gPlayerTexture )
{
    //Show the dot
	gPlayerTexture.render( mBox.x - camera.x, mBox.y - camera.y, gRenderer );
}

bool Player::checkCollision( SDL_Rect a, SDL_Rect b )
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

/*
bool Player::touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= TILE_CENTER ) && ( tiles[ i ]->getType() <= TILE_TOPLEFT ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}*/
