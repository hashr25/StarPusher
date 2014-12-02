#include "GameController.h"
#include "Player.h"

GameController::GameController()
{
    loadLevels();
    currentLevel = 0;
    camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    cameraVelX = 0;
    cameraVelY = 0;
}

bool GameController::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Star Pusher", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				else
                {
                     //Initialize SDL_ttf
                    if( TTF_Init() == -1 )
                    {
                        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                        success = false;
                    }
                }
			}
		}
	}

	return success;
}

bool GameController::loadMedia( SDL_Renderer* gRenderer )
{
	//Loading success flag
	bool success = true;

	//Load Player texture
	if( !gPlayerTexture.loadFromFile( "Images/boy.png", gRenderer ) )
	{
		//std::cout << "Failed to load dot texture!\n" << std::endl;

		success = false;
	}

	//Load tile texture
	if( !gTileTexture.loadFromFile( "Images/StarTiles.png", gRenderer ) )
	{
		//std::cout << "Failed to load tile set texture!\n" << std::endl;
		success = false;
	}

	//Load font
	if( !loadFont( "Test1.ttf" ) )
    {
        //std::cout << "Failed to load font" << std::endl;
    }

    gTileClips[ BOY ].x = 0;
    gTileClips[ BOY ].y = 0;
    gTileClips[ BOY ].w = TILE_WIDTH;
    gTileClips[ BOY ].h = TILE_HEIGHT;

    gTileClips[ CAT_GIRL ].x = 50;
    gTileClips[ CAT_GIRL ].y = 0;
    gTileClips[ CAT_GIRL ].w = TILE_WIDTH;
    gTileClips[ CAT_GIRL ].h = TILE_HEIGHT;

    gTileClips[ HORN_GIRL ].x = 100;
    gTileClips[ HORN_GIRL ].y = 0;
    gTileClips[ HORN_GIRL ].w = TILE_WIDTH;
    gTileClips[ HORN_GIRL ].h = TILE_HEIGHT;

    gTileClips[ PINK_GIRL ].x = 150;
    gTileClips[ PINK_GIRL ].y = 0;
    gTileClips[ PINK_GIRL ].w = TILE_WIDTH;
    gTileClips[ PINK_GIRL ].h = TILE_HEIGHT;

    gTileClips[ PRINCESS ].x = 0;
    gTileClips[ PRINCESS ].y = 85;
    gTileClips[ PRINCESS ].w = TILE_WIDTH;
    gTileClips[ PRINCESS ].h = TILE_HEIGHT;

    gTileClips[ STAR ].x = 50;
    gTileClips[ STAR ].y = 85;
    gTileClips[ STAR ].w = TILE_WIDTH;
    gTileClips[ STAR ].h = TILE_HEIGHT;

    gTileClips[ ON_GOAL ].x = 100;
    gTileClips[ ON_GOAL ].y = 85;
    gTileClips[ ON_GOAL ].w = TILE_WIDTH;
    gTileClips[ ON_GOAL ].h = TILE_HEIGHT;

    gTileClips[ OFF_GOAL ].x = 150;
    gTileClips[ OFF_GOAL ].y = 85;
    gTileClips[ OFF_GOAL ].w = TILE_WIDTH;
    gTileClips[ OFF_GOAL ].h = TILE_HEIGHT;

    gTileClips[ FLOOR ].x = 0;
    gTileClips[ FLOOR ].y = 170;
    gTileClips[ FLOOR ].w = TILE_WIDTH;
    gTileClips[ FLOOR ].h = TILE_HEIGHT;

    gTileClips[ WALL ].x = 50;
    gTileClips[ WALL ].y = 170;
    gTileClips[ WALL ].w = TILE_WIDTH;
    gTileClips[ WALL ].h = TILE_HEIGHT;

    gTileClips[ CORNER ].x = 100;
    gTileClips[ CORNER ].y = 170;
    gTileClips[ CORNER ].w = TILE_WIDTH;
    gTileClips[ CORNER ].h = TILE_HEIGHT;

    gTileClips[ GRASS ].x = 150;
    gTileClips[ GRASS ].y = 170;
    gTileClips[ GRASS ].w = TILE_WIDTH;
    gTileClips[ GRASS ].h = TILE_HEIGHT;

    gTileClips[ ROCK ].x = 0;
    gTileClips[ ROCK ].y = 255;
    gTileClips[ ROCK ].w = TILE_WIDTH;
    gTileClips[ ROCK ].h = TILE_HEIGHT;

    gTileClips[ SHORT_TREE ].x = 50;
    gTileClips[ SHORT_TREE ].y = 255;
    gTileClips[ SHORT_TREE ].w = TILE_WIDTH;
    gTileClips[ SHORT_TREE ].h = TILE_HEIGHT;

    gTileClips[ TALL_TREE ].x = 100;
    gTileClips[ TALL_TREE ].y = 255;
    gTileClips[ TALL_TREE ].w = TILE_WIDTH;
    gTileClips[ TALL_TREE ].h = TILE_HEIGHT;

    gTileClips[ UGLY_TREE ].x = 150;
    gTileClips[ UGLY_TREE ].y = 255;
    gTileClips[ UGLY_TREE ].w = TILE_WIDTH;
    gTileClips[ UGLY_TREE ].h = TILE_HEIGHT;

	/*if( !loadFont( "Test1.ttf" ) )
    {
        //std::cout << "Failed to load font" << std::endl;
    }*/

	return success;
}

bool GameController::loadFont( std::string fileName )
{
    bool success = true;

    font = TTF_OpenFont( fileName.c_str(), 20 );

    if( font == NULL )
    {
        //std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    else
    {
        fontColor = { 255, 255, 255 };
    }


    return success;
}

void GameController::close()
{
	//Free loaded images
	gPlayerTexture.free();
	gTileTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool GameController::touchesWall( SDL_Rect mBox, int x, int y )
{
    bool touchingWall = false;

    //Go through the tiles
//    for( int i = 0; i < gameLevels[currentLevel].getTiles().size(); ++i )
//    {
//        //If the tile is a wall type tile
//        if( ( gameLevels[currentLevel].getTiles()[ i ]->getType() >= WALL ) )
//        {
//            //If the collision box touches the wall tile
//            if( checkCollision( mBox, gameLevels[currentLevel].getTiles()[ i ]->getBox() ) )
//            {
//                return true;
//            }
//        }
//    }

    if ( ( gameLevels[currentLevel].getTiles()[(gameLevels[currentLevel].getLevelWidthInTiles()*y) + x]->getType() == WALL ) || (gameLevels[currentLevel].getTiles()[(gameLevels[currentLevel].getLevelWidthInTiles()*y) + x]->getType() == CORNER ) )
    {
        return true;
    }

    //If no wall tiles were touched
    return false;
}

int GameController::touchesStar(int x, int y)
{
    for ( int i = 0 ; i < gameStars.size() ; i++ )
    {
        if ( (gameStars.at(i).getX() == x ) && ( gameStars.at(i).getY() == y ) )
        {
            return i;
        }
    }
    return -1;
}

bool GameController::starTouchesWall(int x, int y)
{
    if ( ( gameLevels[currentLevel].getTiles()[(gameLevels[currentLevel].getLevelWidthInTiles()*y) + x]->getType() == WALL ) || (gameLevels[currentLevel].getTiles()[(gameLevels[currentLevel].getLevelWidthInTiles()*y) + x]->getType() == CORNER ) )
    {
        return true;
    }
    return false;
}

bool GameController::starTouchesStar(int x, int y)
{
    for ( int i = 0 ; i < gameStars.size() ; i++ )
    {
        if ( (gameStars.at(i).getX() == x ) && ( gameStars.at(i).getY() == y ) )
        {
            return true;
        }
    }
    return false;
}
bool GameController::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + (a.w/2);
    topA = a.y;
    bottomA = a.y + (a.h/2);

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + (b.w/2);
    topB = b.y;
    bottomB = b.y + (b.h/2);

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

bool GameController::setTiles( Tile* tiles[] )
{
	//Success flag
	bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "map1.txt" );

    //If the map couldn't be loaded
    if( map == NULL )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = NO_TYPE;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() )
			{
				//Stop loading map
				//std::cout <<  "Error loading map: Unexpected end of file!" << std::endl;
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TYPES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}

			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;
                y += TILE_FLOOR_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ BOY ].x = 0;
			gTileClips[ BOY ].y = 0;
			gTileClips[ BOY ].w = TILE_WIDTH;
			gTileClips[ BOY ].h = TILE_HEIGHT;

			gTileClips[ CAT_GIRL ].x = 50;
			gTileClips[ CAT_GIRL ].y = 0;
			gTileClips[ CAT_GIRL ].w = TILE_WIDTH;
			gTileClips[ CAT_GIRL ].h = TILE_HEIGHT;

			gTileClips[ HORN_GIRL ].x = 100;
			gTileClips[ HORN_GIRL ].y = 0;
			gTileClips[ HORN_GIRL ].w = TILE_WIDTH;
			gTileClips[ HORN_GIRL ].h = TILE_HEIGHT;

			gTileClips[ PINK_GIRL ].x = 150;
			gTileClips[ PINK_GIRL ].y = 0;
			gTileClips[ PINK_GIRL ].w = TILE_WIDTH;
			gTileClips[ PINK_GIRL ].h = TILE_HEIGHT;

			gTileClips[ PRINCESS ].x = 0;
			gTileClips[ PRINCESS ].y = 85;
			gTileClips[ PRINCESS ].w = TILE_WIDTH;
			gTileClips[ PRINCESS ].h = TILE_HEIGHT;

			gTileClips[ STAR ].x = 50;
			gTileClips[ STAR ].y = 85;
			gTileClips[ STAR ].w = TILE_WIDTH;
			gTileClips[ STAR ].h = TILE_HEIGHT;

			gTileClips[ ON_GOAL ].x = 100;
			gTileClips[ ON_GOAL ].y = 85;
			gTileClips[ ON_GOAL ].w = TILE_WIDTH;
			gTileClips[ ON_GOAL ].h = TILE_HEIGHT;

			gTileClips[ OFF_GOAL ].x = 150;
			gTileClips[ OFF_GOAL ].y = 85;
			gTileClips[ OFF_GOAL ].w = TILE_WIDTH;
			gTileClips[ OFF_GOAL ].h = TILE_HEIGHT;

			gTileClips[ FLOOR ].x = 0;
			gTileClips[ FLOOR ].y = 170;
			gTileClips[ FLOOR ].w = TILE_WIDTH;
			gTileClips[ FLOOR ].h = TILE_HEIGHT;

			gTileClips[ WALL ].x = 50;
			gTileClips[ WALL ].y = 170;
			gTileClips[ WALL ].w = TILE_WIDTH;
			gTileClips[ WALL ].h = TILE_HEIGHT;

			gTileClips[ CORNER ].x = 100;
			gTileClips[ CORNER ].y = 170;
			gTileClips[ CORNER ].w = TILE_WIDTH;
			gTileClips[ CORNER ].h = TILE_HEIGHT;

			gTileClips[ GRASS ].x = 150;
			gTileClips[ GRASS ].y = 170;
			gTileClips[ GRASS ].w = TILE_WIDTH;
			gTileClips[ GRASS ].h = TILE_HEIGHT;

			gTileClips[ ROCK ].x = 0;
			gTileClips[ ROCK ].y = 255;
			gTileClips[ ROCK ].w = TILE_WIDTH;
			gTileClips[ ROCK ].h = TILE_HEIGHT;

			gTileClips[ SHORT_TREE ].x = 50;
			gTileClips[ SHORT_TREE ].y = 255;
			gTileClips[ SHORT_TREE ].w = TILE_WIDTH;
			gTileClips[ SHORT_TREE ].h = TILE_HEIGHT;

			gTileClips[ TALL_TREE ].x = 100;
			gTileClips[ TALL_TREE ].y = 255;
			gTileClips[ TALL_TREE ].w = TILE_WIDTH;
			gTileClips[ TALL_TREE ].h = TILE_HEIGHT;

			gTileClips[ UGLY_TREE ].x = 150;
			gTileClips[ UGLY_TREE ].y = 255;
			gTileClips[ UGLY_TREE ].w = TILE_WIDTH;
			gTileClips[ UGLY_TREE ].h = TILE_HEIGHT;
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

void GameController::runGame( )
{
    //Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//The level tiles
		//Tile* tileSet[ TOTAL_TILES ];

		//Load media
		if( !loadMedia( gRenderer ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
		    resetLevel();

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Level camera
			player.setCamera( camera );

            //where the player was before
            SDL_Rect newPos;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Handle input for the dot
					//player.handleEvent( e, quit, gameLevels[currentLevel].getTiles() );
					moveCamera( e );
					changeLevels( e );

                    SDL_RenderPresent( gRenderer );

                    int star = -1;
                    bool playerCanMove = true;

				//Move the camera
				//player.setCamera( camera );
                    //If a key was pressed
                    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
                    {
                        //Adjust the velocity
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_ESCAPE: quit = true; break;
                            case SDLK_a:
                                {
                                    currentLevel++;
                                    break;
                                }
                            case SDLK_UP:
                            {
                                //std::cout <<"Up\n";

                                SDL_Rect currentPos = player.getBox();
                                newPos.x = currentPos.x;
                                newPos.y = currentPos.y -= TILE_FLOOR_HEIGHT;
                                newPos.h = currentPos.h;
                                newPos.w = currentPos.w;

                                if( touchesWall(newPos, newPos.x/TILE_WIDTH, newPos.y/TILE_FLOOR_HEIGHT) )
                                {
                                  //std::cout<<"Wall\n";
                                }
                                else{

                                    if ( (star = touchesStar(newPos.x/TILE_WIDTH, newPos.y/TILE_FLOOR_HEIGHT) ) >= 0 )
                                    {
                                        if ( starTouchesWall( (newPos.x/TILE_WIDTH) , (newPos.y/TILE_FLOOR_HEIGHT) -1 ) )
                                        {
                                            playerCanMove = false;
                                        }
                                        else if ( starTouchesStar( (newPos.x/TILE_WIDTH) , (newPos.y/TILE_FLOOR_HEIGHT) -1 ) )
                                        {
                                            playerCanMove = false;
                                        }
                                        else
                                        {
                                            gameStars.at(star).setNewPos(newPos.x/TILE_WIDTH, (newPos.y/TILE_FLOOR_HEIGHT) -1 );
                                            playerCanMove = true;
                                        }

                                    }

                                    if (playerCanMove)
                                    {
                                        player.setX(newPos.x);
                                        player.setY(newPos.y);
                                    }

                                }

                                break;
                            }
                            case SDLK_DOWN:
                            {
                                //std::cout <<"Down\n";

                                SDL_Rect currentPos = player.getBox();
                                newPos.x = currentPos.x;
                                newPos.y = currentPos.y += TILE_FLOOR_HEIGHT;
                                newPos.h = currentPos.h;
                                newPos.w = currentPos.w;

                                if( touchesWall( newPos, newPos.x/TILE_WIDTH, newPos.y/TILE_FLOOR_HEIGHT ) )
                                {
                                  //std::cout<<"Wall\n";
                                }
                                else{

                                     if ( (star = touchesStar(newPos.x/TILE_WIDTH, newPos.y/TILE_FLOOR_HEIGHT) ) >= 0 )
                                    {
                                        if ( starTouchesWall( (newPos.x/TILE_WIDTH) , (newPos.y/TILE_FLOOR_HEIGHT) + 1 ) )
                                        {
                                            playerCanMove = false;
                                        }
                                        else if ( starTouchesStar( (newPos.x/TILE_WIDTH) , (newPos.y/TILE_FLOOR_HEIGHT) + 1 ) )
                                        {
                                            playerCanMove = false;
                                        }
                                        else
                                        {
                                            gameStars.at(star).setNewPos(newPos.x/TILE_WIDTH, (newPos.y/TILE_FLOOR_HEIGHT) + 1 );
                                            playerCanMove = true;
                                        }

                                    }

                                    if (playerCanMove)
                                    {
                                        player.setX(newPos.x);
                                        player.setY(newPos.y);
                                    }
                                }
                                break;
                            }
                            case SDLK_LEFT:
                            {
                                //std::cout <<"Left\n";

                                SDL_Rect currentPos = player.getBox();
                                newPos.x = currentPos.x -= TILE_WIDTH;
                                newPos.y = currentPos.y;
                                newPos.h = currentPos.h;
                                newPos.w = currentPos.w;

                                if( touchesWall( newPos, newPos.x/TILE_WIDTH, newPos.y/TILE_FLOOR_HEIGHT ) )
                                {
                                  //std::cout<<"Wall\n";
                                }
                                else{

                                     if ( (star = touchesStar(newPos.x/TILE_WIDTH, newPos.y/TILE_FLOOR_HEIGHT) ) >= 0 )
                                    {
                                        if ( starTouchesWall( (newPos.x/TILE_WIDTH) - 1 , (newPos.y/TILE_FLOOR_HEIGHT) ) )
                                        {
                                            playerCanMove = false;
                                        }
                                        else if ( starTouchesStar( (newPos.x/TILE_WIDTH) - 1 , (newPos.y/TILE_FLOOR_HEIGHT) ) )
                                        {
                                            playerCanMove = false;
                                        }
                                        else
                                        {
                                            gameStars.at(star).setNewPos( (newPos.x/TILE_WIDTH) - 1 , (newPos.y/TILE_FLOOR_HEIGHT) );
                                            playerCanMove = true;
                                        }

                                    }

                                    if (playerCanMove)
                                    {
                                        player.setX(newPos.x);
                                        player.setY(newPos.y);
                                    }
                                }
                                break;
                            }
                            case SDLK_RIGHT:
                            {
                                //std::cout <<"Right\n";

                                SDL_Rect currentPos = player.getBox();
                                newPos.x = currentPos.x += TILE_WIDTH;
                                newPos.y = currentPos.y;
                                newPos.h = currentPos.h;
                                newPos.w = currentPos.w;

                                if( touchesWall( newPos, newPos.x/TILE_WIDTH, newPos.y/TILE_FLOOR_HEIGHT ) )
                                {
                                  //std::cout<<"Wall\n";
                                }
                                else{

                                    if ( (star = touchesStar(newPos.x/TILE_WIDTH, newPos.y/TILE_FLOOR_HEIGHT) ) >= 0 )
                                    {
                                        if ( starTouchesWall( (newPos.x/TILE_WIDTH) + 1, (newPos.y/TILE_FLOOR_HEIGHT) ) )
                                        {
                                            playerCanMove = false;
                                        }
                                        else if ( starTouchesStar( (newPos.x/TILE_WIDTH) + 1, (newPos.y/TILE_FLOOR_HEIGHT) ) )
                                        {
                                            playerCanMove = false;
                                        }
                                        else
                                        {
                                            gameStars.at(star).setNewPos( (newPos.x/TILE_WIDTH) + 1, (newPos.y/TILE_FLOOR_HEIGHT) );
                                            playerCanMove = true;
                                        }

                                    }

                                    if (playerCanMove)
                                    {
                                        player.setX(newPos.x);
                                        player.setY(newPos.y);
                                    }
                                }

                                break;
                            }

                        }
                    }


                }

				//Move the camera
				//player.setCamera( camera );


                if ( levelCompleted() )
                {
                    std::cout << "Conmplete" << std::endl;
                }

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0x66, 0xAA, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				renderLevel();

				//Render player
				player.render( camera, gRenderer, gPlayerTexture );

                //renderWalls();

				player.displaySteps( gRenderer );
				displayLevelNumber();

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}

		//Free resources and close SDL
		close();
	}
}

//Load game levels
void GameController::loadLevels()
{
    std::ifstream inputFile;
    inputFile.open( "convertedMaps.txt" );

    int lineCounter = 0;
    std::string line = "";

    std::vector<std::string> levelLines;
    std::vector<Tile*> levelTiles;

    Level singleLevel;
    Tile* singleTile;

    int levelCounter = 0;
    bool levelDone = false;

    int x = 0;
    int y = 0;
    int tileCounter = 0;

    while( getline( inputFile, line ) )
    {
        if( line.size() > 2 )
        {
            if( line.at(0) == 'j' )
            {
                //std::cout << line << std::endl;

                //lineSS << line;
            }
        }


        ///Finishing Level
        if( lineCounter > 0 && levelDone )
        {//std::cout << "finishing level" << std::endl;
            ///Finishing level
            singleLevel.setTotalTiles();//std::cout << "set total tiles" << std::endl;

            gameLevels[levelCounter] = singleLevel;//std::cout << "Pushed level to vector" << std::endl;
            singleLevel.clear();//std::cout << "cleared singleLevel" << std::endl;
            lineCounter = 0;
            x = 0;
            y = 0;
            tileCounter = 0;

            levelDone = false;
            levelCounter++;
        }

        ///Blank Line
        else if( line.size() < 2 )
        {
            //Leave it alone
        }

        ///Comment Line
        else if( line.at(0) == ';' )
        {
            //Leave it alone too
        }

        ///The actual map lines
        else
        {
            ///Create stringstream to convert lines to integers
            std::stringstream lineSS( line );


            ///First line which holds map sizes
            if( lineCounter == 0 )
            {
                int mapWidth;
                int mapHeight;
                lineSS >> mapWidth;
                lineSS >> mapHeight;//std::cout << "MapWidth: " << mapWidth << "\nMapHeight: " << mapHeight << std::endl;

                //std::cout << "setting map #" << levelCounter <<  " mapHeight to " << mapHeight << std::endl;

                singleLevel.setLevelWidthInTiles( mapWidth );
                singleLevel.setLevelWidthInPixels( mapWidth * TILE_WIDTH );
                singleLevel.setLevelHeightInTiles( mapHeight );
                singleLevel.setLevelHeightInPixels( mapHeight * TILE_FLOOR_HEIGHT );

                lineCounter++;
            }


            ///Middle lines of key, contains the map key itself
            else if( lineCounter >= 1 && lineCounter <= singleLevel.getLevelHeightInTiles()+1 )
            {//std::cout << line <<std::endl;
                for( int i = 0; i < singleLevel.getLevelWidthInTiles(); i++ )
                {
                    std::stringstream tileTypeSS( line.substr(i*3, 3) );
                    int tileType;
                    tileTypeSS >> tileType;

                    //assert( tileType > TOTAL_TYPES );

                    if( tileType >= 0 && tileType < TOTAL_TYPES )
                    {
                        singleTile = new Tile( x, y, tileType );
                        levelTiles.push_back( singleTile );
                        //std::cout << "pushed a tile at " << singleTile -> getBox().x << ", " << singleTile -> getBox().y << " of type " << singleTile -> getType() << std::endl;
                    }

                    tileCounter++;
                    x += TILE_WIDTH;
                }
            }

            ///First line after map key, hold coordinates for player
            else if( lineCounter == 2 + singleLevel.getLevelHeightInTiles() )
            {
                int playerX, playerY;
                lineSS >> playerX;
                lineSS >> playerY;
                singleLevel.setPlayerX( playerX );
                singleLevel.setPlayerY( playerY );
                //std::cout << "placing player at " << playerX << ", " << playerY << std::endl;
            }

            ////std::cout << lineCounter << " : " << singleLevel.getLevelHeightInTiles()+2 << std::endl;
            ///Second line after map key, holds number of stars
            else if( lineCounter == 3 + singleLevel.getLevelHeightInTiles() )
            {//std::cout << line << std::endl;
                //Ending tile creation
                singleLevel.setTiles( levelTiles );//std::cout << "number of total Tiles: " << levelTiles.size() << std::endl;
                levelTiles.clear();//std::cout << "number of total Tiles: " << levelTiles.size() << std::endl;

                //Setting up number of stars
                int numberOfStars;
                lineSS >> numberOfStars;
                singleLevel.setNumberOfStars( numberOfStars );
            }

            ///Third line after map key, coordinates for stars
            else if( lineCounter == ( 4 + singleLevel.getLevelHeightInTiles() ) )
            {//std::cout << line << std::endl;
                for( int i = 0; i < singleLevel.getNumberOfStars(); i++ )
                {
                    int starX, starY;
                    lineSS >> starX;
                    lineSS >> starY;

                    Star thisStar( starX, starY );
                    singleLevel.addStar( thisStar );//std::cout << "Creating star at " << starX << ", " << starY << std::endl;
                }

                levelDone = true;//std::cout << "Changed levelDone flag to True" << std::endl;
            }

            ///This only returns the carriage for tile display coordinates
            if( x >= singleLevel.getLevelWidthInPixels() )
            {
                x = 0;
                y += TILE_FLOOR_HEIGHT;
            }

            //levelLines.push_back( line );
            lineCounter++;
        }
    }
}

void GameController::changeLevels( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_n: nextLevel(); break;
            case SDLK_p: previousLevel(); break;
            case SDLK_r: resetLevel(); break;
        }
    }
}

Level* GameController::getLevels()
{
    return gameLevels;
}

void GameController::displayLevelNumber()
{
    LTexture levelTexture;
    std::stringstream levelSS;

    levelSS << "Level " << currentLevel+1 << " of " << TOTAL_LEVELS;

    std::string levelOutput = levelSS.str();

    levelTexture.loadFromRenderedText( levelOutput, fontColor, font, gRenderer );

    levelTexture.render( 25, 420, gRenderer );
}

void GameController::moveCamera( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: cameraVelY -= CAMERA_SPEED; break;
            case SDLK_a: cameraVelX -= CAMERA_SPEED; break;
            case SDLK_s: cameraVelY += CAMERA_SPEED; break;
            case SDLK_d: cameraVelX += CAMERA_SPEED; break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: cameraVelY += CAMERA_SPEED; break;
            case SDLK_a: cameraVelX += CAMERA_SPEED; break;
            case SDLK_s: cameraVelY -= CAMERA_SPEED; break;
            case SDLK_d: cameraVelX -= CAMERA_SPEED; break;
        }
    }


    //Move the Player left or right
    camera.x += cameraVelX;

    //If the Player went too far to the left or right or touched a wall
    /*if( ( camera.x < 0 ) || ( camera.x > LEVEL_WIDTH ) )
    {
        //move back
        camera.x -= cameraVelX;
    }*/


    //Move the Player up or down
    camera.y += cameraVelY;

    //If the Player went too far up or down or touched a wall
    /*if( ( camera.y < 0 ) || ( camera.y > LEVEL_HEIGHT ) )
    {
        //move back
        camera.y -= cameraVelY;
    }*/

    if( camera.x  < 60 - gameLevels[currentLevel].getLevelWidthInPixels() )
	{
		camera.x = 60 - gameLevels[currentLevel].getLevelWidthInPixels();
	}
	if( camera.y < 100 - gameLevels[currentLevel].getLevelHeightInPixels() )
	{
		camera.y = 100 - gameLevels[currentLevel].getLevelHeightInPixels();
	}
	if( camera.x > gameLevels[currentLevel].getLevelWidthInPixels() - 245)
	{
		camera.x = gameLevels[currentLevel].getLevelWidthInPixels() - 245;
	}
	if( camera.y > gameLevels[currentLevel].getLevelHeightInPixels() - 180)
	{
		camera.y = gameLevels[currentLevel].getLevelHeightInPixels() - 180;
	}
}

//Level Methods
void GameController::renderLevel()
{
    for( int i = 0; i < gameLevels[ currentLevel ].getTiles().size(); i++ )
    {
        gameLevels[ currentLevel ].getTiles()[i] -> render( camera, gRenderer, gTileClips, gTileTexture );
    }
    for( int i = 0; i < gameStars.size(); i++ )
    {
        if ( gameLevels[currentLevel].getTiles()[(gameLevels[currentLevel].getLevelWidthInTiles()*gameStars.at(i).getY()) + gameStars.at(i).getX()]->getType() == OFF_GOAL )
        {
            gameLevels[currentLevel].getTiles()[(gameLevels[currentLevel].getLevelWidthInTiles()*gameStars.at(i).getY()) + gameStars.at(i).getX()]->setType(ON_GOAL);
        }

        gameStars.at(i).render( camera, gRenderer, gTileClips, gTileTexture );
    }
}

void GameController::nextLevel()
{
    if( currentLevel < 201 )
    {
        currentLevel++;
        //std::cout << "moving player to " << gameLevels[currentLevel].getPlayerX() << ", " << gameLevels[currentLevel].getPlayerY() << std::endl;
        player.setPosition( gameLevels[currentLevel].getPlayerX(), gameLevels[currentLevel].getPlayerY() );
        gameStars = gameLevels[ currentLevel ].getStars();
        player.setSteps(0);
        centerCamera();
    }
}

void GameController::previousLevel()
{
    if( currentLevel > 0 )
    {
        currentLevel--;
        //std::cout << "moving player to " << gameLevels[currentLevel].getPlayerX() << ", " << gameLevels[currentLevel].getPlayerY() << std::endl;
        player.setPosition( gameLevels[currentLevel].getPlayerX(), gameLevels[currentLevel].getPlayerY() );
        gameStars = gameLevels[ currentLevel ].getStars();
        player.setSteps(0);
        centerCamera();
    }
}

void GameController::resetLevel()
{
    //std::cout << "moving player to " << gameLevels[currentLevel].getPlayerX() << ", " << gameLevels[currentLevel].getPlayerY() << std::endl;
    player.setPosition( gameLevels[currentLevel].getPlayerX(), gameLevels[currentLevel].getPlayerY() );
    gameStars = gameLevels[ currentLevel ].getStars();
    player.setSteps(0);
    centerCamera();
}

void GameController::centerCamera()
{
    camera.x = ( player.getBox().x + PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( player.getBox().y + PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
}

bool GameController::levelCompleted()
{
    for ( int i = 0 ; i < gameStars.size() ; i++ )
    {
        if ( ( gameLevels[currentLevel].getTiles()[(gameLevels[currentLevel].getLevelWidthInTiles()*gameStars.at(i).getY()) + gameStars.at(i).getX()]->getType() != ON_GOAL ) )
        {
            return false;
        }
    }
    return true;
}
