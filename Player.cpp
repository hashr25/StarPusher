#include "Player.h"
#include "GameController.h"
#include "Tile.h"

///Constructors and Destructors
Player::Player()
{
    steps = 0;

    mBox.x = 250;
    mBox.y = 180;

    //Initialize the collision box
	mBox.w = PLAYER_WIDTH;
	mBox.h = PLAYER_HEIGHT;

<<<<<<< HEAD
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //load font
    TTF_Init();
    loadFont( "Test1.ttf" );
=======
    //load font
    //loadFont( "Test1.ttf" );
>>>>>>> origin/CharlotteRose
}

Player::~Player()
{
    TTF_CloseFont( font );
}

///Getters and Setters
//Getters
int Player::getSteps()
{
    return steps;
}

SDL_Rect Player::getBox()
{
    return mBox;
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

//Set position
void Player::setPosition( int xPosition, int yPosition )
{
    mBox.x = xPosition * TILE_WIDTH;
    mBox.y = yPosition * TILE_FLOOR_HEIGHT;
}

//Get box
SDL_Rect Player::getBox()
{
    return mBox;
}

///Methods
void Player::handleEvent( SDL_Event& e, bool& exitFlag )
{
    if( e.type == SDL_QUIT )
    {
        exitFlag = true;
        //std::cout << "Trying to leave" << std::endl;
    }
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_ESCAPE: exitFlag = true; break;
<<<<<<< HEAD
            case SDLK_UP: mBox.y -= TILE_FLOOR_HEIGHT; oneMoreStep(); break;
            case SDLK_DOWN: mBox.y += TILE_FLOOR_HEIGHT; oneMoreStep(); break;
            case SDLK_LEFT: mBox.x -= TILE_WIDTH; oneMoreStep(); break;
            case SDLK_RIGHT: mBox.x += TILE_WIDTH; oneMoreStep(); break;
=======
            case SDLK_UP:
                {
                    mBox.y -= TILE_FLOOR_HEIGHT; oneMoreStep(); break;
                }
            case SDLK_DOWN:
                {
                    mBox.y += TILE_FLOOR_HEIGHT; oneMoreStep(); break;
                }
            case SDLK_LEFT:
                {
                     mBox.x -= TILE_FLOOR_HEIGHT; oneMoreStep(); break;
                }
            case SDLK_RIGHT:
                {
                     mBox.x += TILE_FLOOR_HEIGHT; oneMoreStep(); break;
                }
>>>>>>> origin/CharlotteRose
        }
    }
}
/*
void Player::move(Tile *tiles[])
{
    mBox.y -= TILE_FLOOR_HEIGHT; //moving up
    if ( mBox.y < 0 )
    {
        mBox.y += TILE_FLOOR_HEIGHT;
    }

    mBox.y += TILE_FLOOR_HEIGHT; // moving down
    if ( mBox.y > LEVEL_HEIGHT )
    {
        mBox.y -= TILE_FLOOR_HEIGHT;
    }

    mBox.x -= TILE_WIDTH;
    if ( mBox.x < 0)
    {
        mBox.x += TILE_WIDTH;
    }

    mBox.x += TILE_WIDTH;
    if ( mBox.x > LEVEL_WIDTH)
    {
        mBox.x -= TILE_WIDTH;
    }
    //Up move
    if( ( mBox.y < 1) || touchesWall( mBox, tiles ) != 4 )
    {
    //move forward
        mBox.y += ( TILE_FLOOR_HEIGHT + 1) ;
    }
    else
    {
        mBox.y -= TILE_FLOOR_HEIGHT;
    }
    //Down Move
    if( ( mBox.y + PLAYER_HEIGHT > (LEVEL_HEIGHT - PLAYER_HEIGHT) ) /*|| touchesWall( mBox, tiles )/ )
    {
        //move back
        mBox.y -= ( TILE_FLOOR_HEIGHT - 1 );
    }
    else
    {
        mBox.y += TILE_FLOOR_HEIGHT; oneMoreStep();
    }
    //Left Move
    if( ( mBox.x < 0 ) /*|| ( mBox.x - PLAYER_WIDTH < LEVEL_WIDTH ) /*|| touchesWall( mBox, tiles )/ )
    {
        //move right
        mBox.x += TILE_WIDTH;
    }
    else
    {
        mBox.x -= TILE_WIDTH;
    }
    //Right Move
    if( ( mBox.x == LEVEL_WIDTH - 1 ) || ( mBox.x + PLAYER_WIDTH > LEVEL_WIDTH ) /*|| touchesWall( mBox, tiles )/ )
    {
        //move left
        mBox.x -= TILE_WIDTH ;
    }
    else
    {
        mBox.x += TILE_WIDTH;
    }


   /* if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.x -= mVelX;
    }

    //If the dot went too far up or down or touched a wall
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.y -= mVelY;
    }
}*/

void Player::setX(int newX)
{
    mBox.x = newX;
}

void Player::setY(int newY)
{
    mBox.y = newY;
}

void Player::setCamera( SDL_Rect& camera )
{
	//Center the camera over the Player
	camera.x = ( mBox.x + PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
<<<<<<< HEAD
	/*if( camera.x < 0 - LEVEL_WIDTH)
=======
	/*if( camera.x < 0 - TILE_WIDTH)
>>>>>>> origin/CharlotteRose
	{
		camera.x = 0;
	}
	if( camera.y < 0 - TILE_HEIGHT )
	{
		camera.y = 0;
	}
<<<<<<< HEAD
	if( camera.x > LEVEL_WIDTH )
	{
		camera.x = LEVEL_WIDTH;
	}
	if( camera.y > LEVEL_HEIGHT )
	{
		camera.y = LEVEL_HEIGHT;
=======
	if( camera.x > TILE_WIDTH )
	{
		camera.x = TILE_WIDTH;
	}
	if( camera.y > TILE_HEIGHT )
	{
		camera.y = TILE_HEIGHT;
>>>>>>> origin/CharlotteRose
	}*/
}



void Player::render( SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& gPlayerTexture )
{
        //Show the Player
        gPlayerTexture.render( mBox.x- camera.x, mBox.y - camera.y, gRenderer );
}

/*int Player::checkCollision( SDL_Rect a, SDL_Rect b )
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
        return 0;
    }

    if( topA >= bottomB )
    {
        return 1;
    }

    if( rightA <= leftB )
    {
        return 2;
    }

    if( leftA >= rightB )
    {
        return 3;
    }

    //If none of the sides from A are outside B
    return 4;
}

bool Player::touchesWall( SDL_Rect mBox, Tile* tiles[] )
{
    //Go through the tiles


    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= WALL ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( mBox, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
<<<<<<< HEAD
}*/

=======
}
*/
/*
>>>>>>> origin/CharlotteRose
void Player::displaySteps( SDL_Renderer* gRenderer )
{
    LTexture stepTexture;
    std::stringstream stepsSS;
    stepsSS << steps;
    std::string stepsOutput = "Steps: " + stepsSS.str();

    stepTexture.loadFromRenderedText( stepsOutput, fontColor, font, gRenderer );

    stepTexture.render( 25, 445, gRenderer );
}

<<<<<<< HEAD
=======

>>>>>>> origin/CharlotteRose
bool Player::loadFont( std::string fileName )
{
    bool success = true;

    font = TTF_OpenFont( fileName.c_str(), 20 );

    if( font == NULL )
    {
<<<<<<< HEAD
        //std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
=======
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
>>>>>>> origin/CharlotteRose
        success = false;
    }

    else
    {
        fontColor = { 255, 255, 255 };
    }

    return success;
}
<<<<<<< HEAD
=======
*/
>>>>>>> origin/CharlotteRose
