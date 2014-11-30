#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <cassert>
#include <iostream>

#include "EnumTypes.h"
#include "LTexture.h"

//The tile
class Tile
{
    public:
		//Initializes position and type
		Tile();
		Tile( int x, int y, int TileType );

		//Shows the tile
		void render( SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect gTileClips[ TOTAL_TYPES ], LTexture& gTileTexture );

		//Get the tile type
		int getType();
		void setType( int type );

		void setX( int x );
		void setY( int y );
		void setPosition( int x, int y );

		//Get the collision box
		SDL_Rect getBox();

		//Check collision
		bool checkCollision( SDL_Rect a, SDL_Rect b );

    private:
		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		int mType;
};
#endif // TILE_H
