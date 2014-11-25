#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cassert>

#include "Tile.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool initSDL( SDL_Window*&, SDL_Renderer*& );
SDL_Texture* loadTexture( std::string, SDL_Renderer* renderer );
void closeSDL( SDL_Window*, SDL_Renderer*, SDL_Texture* );

int main( int argc, char* argv[] )
{
    SDL_Window* testWindow;
    SDL_Renderer* testRenderer;
    initSDL( testWindow, testRenderer );
    SDL_Texture* testTexture = loadTexture( "Grass_Block.bmp", testRenderer );

    Tile testGrassTile( 0, 0, GRASS, testTexture );

    SDL_RenderClear( testRenderer );

    for( int i = 0; i < 14; i++ )
    {
        testGrassTile.setMapY(i);

        for( int j = 0; j < 16; j++ )
        {
            testGrassTile.setMapX(j);
            testGrassTile.displayTile( testRenderer );
        }
    }

    SDL_RenderPresent( testRenderer );

    SDL_Delay(5000);

    return 0;
}

bool initSDL( SDL_Window*& window, SDL_Renderer*& renderer )
{
    bool success;
    //Create window
    window = SDL_CreateWindow( "Testing Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        //Create renderer for window
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if( renderer == NULL )
        {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                success = false;
            }
        }
    }

    return success;
}

SDL_Texture* loadTexture( std::string path, SDL_Renderer* renderer )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image! SDL_image Error: " << path.c_str() << IMG_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            std::cout << "Unable to create texture from! SDL Error: " << path.c_str() << SDL_GetError() << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void closeSDL( SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture )
{
    //Free loaded image
    SDL_DestroyTexture( texture );
    texture = NULL;

    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
