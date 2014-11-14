/*This source code copyrighted by Lazy Foo' Productions (2004-2014)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "LTexture.h"
#include "Tile.h"
#include "EnumTypes.h"
#include "Player.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//Checks collision box against set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gPlayerTexture;
LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TEXTURES ];

bool init()
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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
			}
		}
	}

	return success;
}

bool loadMedia( Tile* tiles[], SDL_Renderer* gRenderer )
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gPlayerTexture.loadFromFile( "Images/boy.png", gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
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

	return success;
}

void close( Tile* tiles[] )
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

bool checkCollision( SDL_Rect a, SDL_Rect b )
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

bool setTiles( Tile* tiles[] )
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
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TEXTURES ) )
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
			gTileClips[ BOY_IMG ].x = 0;
			gTileClips[ BOY_IMG ].y = 0;
			gTileClips[ BOY_IMG ].w = TILE_WIDTH;
			gTileClips[ BOY_IMG ].h = TILE_HEIGHT;

			gTileClips[ CAT_GIRL_IMG ].x = 50;
			gTileClips[ CAT_GIRL_IMG ].y = 0;
			gTileClips[ CAT_GIRL_IMG ].w = TILE_WIDTH;
			gTileClips[ CAT_GIRL_IMG ].h = TILE_HEIGHT;

			gTileClips[ HORN_GIRL_IMG ].x = 100;
			gTileClips[ HORN_GIRL_IMG ].y = 0;
			gTileClips[ HORN_GIRL_IMG ].w = TILE_WIDTH;
			gTileClips[ HORN_GIRL_IMG ].h = TILE_HEIGHT;

			gTileClips[ PINK_GIRL_IMG ].x = 150;
			gTileClips[ PINK_GIRL_IMG ].y = 0;
			gTileClips[ PINK_GIRL_IMG ].w = TILE_WIDTH;
			gTileClips[ PINK_GIRL_IMG ].h = TILE_HEIGHT;

			gTileClips[ PRINCESS_IMG ].x = 0;
			gTileClips[ PRINCESS_IMG ].y = 85;
			gTileClips[ PRINCESS_IMG ].w = TILE_WIDTH;
			gTileClips[ PRINCESS_IMG ].h = TILE_HEIGHT;

			gTileClips[ STAR_IMG ].x = 50;
			gTileClips[ STAR_IMG ].y = 85;
			gTileClips[ STAR_IMG ].w = TILE_WIDTH;
			gTileClips[ STAR_IMG ].h = TILE_HEIGHT;

			gTileClips[ ON_GOAL_IMG ].x = 100;
			gTileClips[ ON_GOAL_IMG ].y = 85;
			gTileClips[ ON_GOAL_IMG ].w = TILE_WIDTH;
			gTileClips[ ON_GOAL_IMG ].h = TILE_HEIGHT;

			gTileClips[ OFF_GOAL_IMG ].x = 150;
			gTileClips[ OFF_GOAL_IMG ].y = 85;
			gTileClips[ OFF_GOAL_IMG ].w = TILE_WIDTH;
			gTileClips[ OFF_GOAL_IMG ].h = TILE_HEIGHT;

			gTileClips[ FLOOR_IMG ].x = 0;
			gTileClips[ FLOOR_IMG ].y = 170;
			gTileClips[ FLOOR_IMG ].w = TILE_WIDTH;
			gTileClips[ FLOOR_IMG ].h = TILE_HEIGHT;

			gTileClips[ WALL_IMG ].x = 50;
			gTileClips[ WALL_IMG ].y = 170;
			gTileClips[ WALL_IMG ].w = TILE_WIDTH;
			gTileClips[ WALL_IMG ].h = TILE_HEIGHT;

			gTileClips[ CORNER_IMG ].x = 100;
			gTileClips[ CORNER_IMG ].y = 170;
			gTileClips[ CORNER_IMG ].w = TILE_WIDTH;
			gTileClips[ CORNER_IMG ].h = TILE_HEIGHT;

			gTileClips[ GRASS_IMG ].x = 150;
			gTileClips[ GRASS_IMG ].y = 170;
			gTileClips[ GRASS_IMG ].w = TILE_WIDTH;
			gTileClips[ GRASS_IMG ].h = TILE_HEIGHT;

			gTileClips[ ROCK_IMG ].x = 0;
			gTileClips[ ROCK_IMG ].y = 255;
			gTileClips[ ROCK_IMG ].w = TILE_WIDTH;
			gTileClips[ ROCK_IMG ].h = TILE_HEIGHT;

			gTileClips[ SHORT_TREE_IMG ].x = 50;
			gTileClips[ SHORT_TREE_IMG ].y = 255;
			gTileClips[ SHORT_TREE_IMG ].w = TILE_WIDTH;
			gTileClips[ SHORT_TREE_IMG ].h = TILE_HEIGHT;

			gTileClips[ TALL_TREE_IMG ].x = 100;
			gTileClips[ TALL_TREE_IMG ].y = 255;
			gTileClips[ TALL_TREE_IMG ].w = TILE_WIDTH;
			gTileClips[ TALL_TREE_IMG ].h = TILE_HEIGHT;

			gTileClips[ UGLY_TREE_IMG ].x = 150;
			gTileClips[ UGLY_TREE_IMG ].y = 255;
			gTileClips[ UGLY_TREE_IMG ].w = TILE_WIDTH;
			gTileClips[ UGLY_TREE_IMG ].h = TILE_HEIGHT;
		}
	}

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

int main( int argc, char* args[] )
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

			//The dot that will be moving around on the screen
			Player player;

			//Level camera
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

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
					player.handleEvent( e );
				}

				//Move the dot
				player.move( tileSet );
				player.setCamera( camera );

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xAA, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera, gRenderer, gTileClips, gTileTexture );
				}

				//Render dot
				player.render( camera, gRenderer, gPlayerTexture );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}

		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}
