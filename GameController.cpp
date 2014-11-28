#include "GameController.h"
#include "Player.h"

GameController::GameController()
{
//    loadLevels();
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

bool GameController::loadMedia( Tile* tiles[], SDL_Renderer* gRenderer )
{
	//Loading success flag
	bool success = true;

	//Load Player texture
	if( !gPlayerTexture.loadFromFile( "Images/boy.png", gRenderer ) )
	{
		printf( "Failed to load Player texture!\n" );
		success = false;
	}

	//Load tile texture
	if( !gTileTexture.loadFromFile( "Images/StarTiles.png", gRenderer ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}

	/*if( !loadFont( "Test1.ttf" ) )
    {
        std::cout << "Failed to load font" << std::endl;
    }*/

	return success;
}
/*
bool GameController::loadFont( std::string fileName )
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
*/
void GameController::close( Tile* tiles[] )
{
	//Deallocate tiles
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] == NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}

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

bool GameController::touchesWall( SDL_Rect mBox, Tile* tiles[] )
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

/// //////////////////////////////////////////////////////////////////////////////////////
/// WHERE THE SAME THING ACTUALLY WORKS
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
				std::cout <<  "Error loading map: Unexpected end of file!" << std::endl;
				tilesLoaded = false;
				break;
			}

/// //////////////////////////////////////////////////////////////////////////////////////
/// Works here

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TEXTURES ) )
			{
				tiles[ i ] = new Tile( x, y, tileType );
			}

/// Works here
/// ///////////////////////////////////////////////////////////////////////////////////////

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

				//Move to the next row
				//if( y == 0 )
                //{
                //    y += TILE_HEIGHT;
                //}

                //else
                //{
                    y += TILE_FLOOR_HEIGHT;
                //}

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
/// WHERE THE SAME THING ACTUALLY WORKS
/// //////////////////////////////////////////////////////////////////////////////////////

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
		Tile* tileSet[ TOTAL_TILES ];

		//Load media
		if( !loadMedia( tileSet, gRenderer ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The Player that will be moving around on the screen
			Player player;

			//Level camera
			player.setCamera( camera );

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{std::cout << "Trying to Quit" << std::endl;
						quit = true;
					}

					//Handle input for the Player

                    player.handleEvent( e, quit );
                }
                SDL_Rect mBox = player.getBox();
                player.move( tileSet, touchesWall( tileSet, mBox  ));
                moveCamera( e );

				//Move the camera
				//player.setCamera( camera );

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0x66, 0xAA, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera, gRenderer, gTileClips, gTileTexture );
				}

				//Render player
				player.render( camera, gRenderer, gPlayerTexture );
				//player.displaySteps( gRenderer );
				//displayLevelNumber();

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}

		//Free resources and close SDL
		close( tileSet );
	}
}
/*
//Load game levels
/// //////////////////////////////////////////////////////////////////////////////////////
/// WHERE THE PART OF CODE THAT CRASHES IS
void GameController::loadLevels()
{
    std::ifstream inputFile;
    inputFile.open( "convertedMaps.txt" );

    int lineCounter = 0;
    std::string line = "";

    std::vector<std::string> levelLines;
    Level eachLevel;

    int levelCounter = 0;

    int x = 0;
    int y = 0;
    int tileCounter = 0;

    while( getline( inputFile, line ) )
    {
        if( line.size() > 2 )
        {
            if( line.at(0) == 'j' )
            {
                std::cout << line << std::endl;

                //lineSS << line;
            }
        }


        ///Finishing Level
        if( lineCounter > 0 && line.size() < 2 )
        {
            ///Finishing level
            gameLevels.push_back( eachLevel );
            eachLevel.clear();
            lineCounter = 0;
            x = 0;
            y = 0;
            tileCounter = 0;

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
            std::stringstream lineSS( line );
            /// ////////////////////////////////////////////////
            /// BUGGED SECTION

            ///First line which holds map sizes

            if( lineCounter == 0 )
            {
                int mapWidth;
                int mapHeight;
                lineSS >> mapWidth;
                lineSS >> mapWidth;
                eachLevel.setLevelWidthInTiles( mapWidth );
                eachLevel.setLevelWidthInPixels( mapWidth * TILE_WIDTH );
                eachLevel.setLevelHeightInTiles( mapHeight );
                eachLevel.setLevelHeightInPixels( mapHeight * TILE_FLOOR_HEIGHT );
            }

            /// BUGGED SECTION

            /// //////////////////////////////////////////////////////////////////////


            ///Middle lines of key, contains the map key itself
            if( lineCounter >= 1 && lineCounter <= eachLevel.getLevelHeightInTiles()+1 )
            {
                for( int i = 0; i < line.size(); i++ )
                {
                    ///Used for Testing
                    //std::cout << levelCounter << " - " << x << " x " << y << std::endl;
                    //std::cout << "TileCounter: " << tileCounter << std::endl;

                    int tileType;
                    lineSS >> tileType;

/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// BUGGED SECTION CAUSING CRASH

                    if( tileType >= 0 && tileType < TOTAL_TEXTURES )
                    {
                        ///eachLevel.tiles[ tileCounter ] = new Tile( x, y, tileType );
                    }

/// BUGGED SECTION CAUSING CRASH
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                    tileCounter++;
                    x += TILE_WIDTH;
                }
            }


            ///First line after map key, holds number of stars
            if( lineCounter == (2 + eachLevel.getLevelHeightInTiles() ) )
            {
                int numberOfStars;
                lineSS >> numberOfStars;
                eachLevel.setNumberOfStars( numberOfStars );
            }

            ///Coordinates for stars
            if( lineCounter == ( 3 + eachLevel.getLevelHeightInTiles() ) )
            {
                for( int i = 0; i < eachLevel.getNumberOfStars(); i++ )
                {
                    int starX, starY;
                    lineSS >> starX >> starY;
                    Star thisStar( starX, starY );
                    eachLevel.addStar( thisStar );
                }
            }

            ///This only returns the carriage for tile display coordinates
            if( x >= eachLevel.getLevelWidthInPixels() )
            {
                x = 0;
                y += TILE_FLOOR_HEIGHT;
            }

            levelLines.push_back( line );
            lineCounter++;
        }
    }
}
/// WHERE THE PART OF CODE THAT CRASHES IS
/// //////////////////////////////////////////////////////////////////////////////////////

std::vector<Level> GameController::getLevels()
{
    return gameLevels;
}
*/
void GameController::displayLevelNumber()
{
    LTexture levelTexture;
    std::stringstream levelSS;
    levelSS << "Level " << currentLevel << " of " << gameLevels.size();
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
}
