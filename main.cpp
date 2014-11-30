/*This source code copyrighted by Lazy Foo' Productions (2004-2014)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <fstream>

#include "LTexture.h"
#include "Tile.h"
#include "EnumTypes.h"
#include "Player.h"
#include "GameController.h"

int main( int argc, char* args[] )
{
	GameController StarPusher;
	StarPusher.runGame();

	return 0;
}
