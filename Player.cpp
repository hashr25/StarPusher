#include "Player.h"

///Constructors and Destructors
Player::Player()
{
    steps = 0;

    mBox.x = 250;
    mBox.y = 250;

    //Initialize the collision box
	mBox.w = PLAYER_WIDTH;
	mBox.h = PLAYER_HEIGHT;

    //load font
    loadFont( "Test1.ttf" );
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
void Player::handleEvent( SDL_Event& e, bool& exitFlag )
{
    if( e.type == SDL_QUIT )
    {
        exitFlag = true;
        std::cout << "Trying to leave" << std::endl;
    }
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_ESCAPE: exitFlag = true; break;
            case SDLK_UP:
                //If the dot went too far up or down or touched a wall
                if( ( mBox.y < 0 ) || ( mBox.y + PLAYER_WIDTH > LEVEL_HEIGHT ) /*|| touchesWall( mBox, tiles ) */)
                {
                    //move back
                    mBox.y += TILE_FLOOR_HEIGHT;
                }
                else
                {
                    mBox.y -= TILE_FLOOR_HEIGHT; oneMoreStep(); break;
                }
            case SDLK_DOWN:
                //If the dot went too far up or down or touched a wall
                if( /*( mBox.y > 0 ) ||*/ ( mBox.y + PLAYER_WIDTH > LEVEL_HEIGHT ) /*|| touchesWall( mBox, tiles ) */)
                {
                    //move back
                    mBox.y -= TILE_FLOOR_HEIGHT;
                }
                else
                {
                    mBox.y += TILE_FLOOR_HEIGHT; oneMoreStep(); break;
                }
            case SDLK_LEFT:
                if( ( mBox.x < 0 ) || ( mBox.x + PLAYER_WIDTH > LEVEL_WIDTH ) /*|| touchesWall( mBox, tiles ) */)
                {
                    //move back
                    mBox.x += TILE_FLOOR_HEIGHT;
                }
                else
                {
                     mBox.x -= TILE_FLOOR_HEIGHT; oneMoreStep(); break;
                }

            case SDLK_RIGHT:
            if( ( mBox.y == 0 ) || ( mBox.x + PLAYER_WIDTH > LEVEL_WIDTH ) /*|| touchesWall( mBox, tiles ) */)
                {
                    //move back
                    mBox.x -= TILE_FLOOR_HEIGHT;
                }
                else
                {
                     mBox.x += TILE_FLOOR_HEIGHT; oneMoreStep(); break;
                }
        }
    }
}

void Player::setCamera( SDL_Rect& camera )
{
	//Center the camera over the Player
	camera.x = ( mBox.x + PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	/*if( camera.x < 0 - TILE_WIDTH)
	{
		camera.x = 0;
	}
	if( camera.y < 0 - TILE_HEIGHT )
	{
		camera.y = 0;
	}
	if( camera.x > TILE_WIDTH )
	{
		camera.x = TILE_WIDTH;
	}
	if( camera.y > TILE_HEIGHT )
	{
		camera.y = TILE_HEIGHT;
	}*/
}



void Player::render( SDL_Rect& camera, SDL_Renderer* gRenderer, LTexture& gPlayerTexture )
{
    //Show the Player
	gPlayerTexture.render( mBox.x- camera.x, mBox.y - camera.y, gRenderer );
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

void Player::displaySteps( SDL_Renderer* gRenderer )
{
    LTexture stepTexture;
    std::stringstream stepsSS;
    stepsSS << steps;
    std::string stepsOutput = "Steps: " + stepsSS.str();

    stepTexture.loadFromRenderedText( stepsOutput, fontColor, font, gRenderer );

    stepTexture.render( 25, 445, gRenderer );
}

bool Player::loadFont( std::string fileName )
{
    bool success = true;

    font = TTF_OpenFont( fileName.c_str(), 20 );

    if( font == NULL )
    {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    else
    {
        fontColor = { 255, 255, 255 };
    }

    return success;
}
