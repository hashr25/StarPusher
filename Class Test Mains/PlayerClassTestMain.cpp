#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cassert>

#include "Tile.h"
#include "Player.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool initSDL( SDL_Window*&, SDL_Renderer*& );
SDL_Texture* loadTexture( std::string, SDL_Renderer* renderer );
bool loadMedia( SDL_Texture** gameTextures, SDL_Renderer* renderer );
void closeSDL( SDL_Window*, SDL_Renderer*, SDL_Texture* );
void displayStuff( Tile gameMap[][8], Player testPlayer, SDL_Renderer* testRenderer );
bool pollForExit();

int main( int argc, char* argv[] )
{
    SDL_Window* testWindow;
    SDL_Renderer* testRenderer;
    initSDL( testWindow, testRenderer );

    SDL_Texture* testTextures[TOTAL_TEXTURES];
    loadMedia( testTextures, testRenderer );

    Tile testGrassTile( 0, 0, GRASS, testTextures[GRASS_IMG] );
    Player testPlayer(3, 3, PLAYER, testTextures[PLAYER_IMG] );

    SDL_RenderClear( testRenderer );

    Tile gameMap[8][8];
    for( int i = 0; i < 8; i++ )
    {
        testGrassTile.setMapY(i);

        for( int j = 0; j < 8; j++ )
        {
            testGrassTile.setMapX(j);
            gameMap[i][j] = testGrassTile;
        }
    }

    bool quit = false;
    while( !quit )
    {
        displayStuff( gameMap, testPlayer, testRenderer );
        testPlayer.getMove( quit );
        SDL_RenderPresent( testRenderer );
        std::cout << "Steps: " << testPlayer.getSteps() << std::endl;
    }

    SDL_RenderPresent( testRenderer );

    SDL_Delay(5000);

    return 0;
}

bool initSDL( SDL_Window*& window, SDL_Renderer*& renderer )
{
    bool success;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    else
    {
        //Create window
        window = SDL_CreateWindow( "Testing Player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

bool loadMedia( SDL_Texture** gameTextures, SDL_Renderer* renderer )
{
    //Loading success flag
    bool success = true;

    //Load PNG Texture
    gameTextures[ GRASS_IMG ] = loadTexture( "Grass_Block.png", renderer );
    if( gameTextures[ GRASS_IMG ] == NULL )
    {
        std::cout << "Failed to load grass texture image!" << std::endl;
        success = false;
    }

    gameTextures[ PLAYER_IMG ] = loadTexture( "princess.png", renderer );
    if( gameTextures[PLAYER_IMG ] == NULL )
    {
        std::cout << "Failed to load player texture image!" << std::endl;
        success = false;
    }

    return success;
}

void closeSDL( SDL_Window* window, SDL_Renderer* renderer, SDL_Texture** textures )
{
    //Free loaded image
    for( int i = 0; i < TOTAL_TEXTURES; i++ )
    {
        SDL_DestroyTexture( textures[i] );
        textures[i] = NULL;
    }


    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void displayStuff( Tile gameMap[][8], Player testPlayer, SDL_Renderer* testRenderer )
{
    for( int i = 0; i < 8; i++ )
    {
        for( int j = 0; j < 8; j++ )
        {
            gameMap[i][j].displayTile( testRenderer );
        }
    }
    testPlayer.displayTile( testRenderer );
}

bool pollForExit()
{
    SDL_Event keyPress;
    bool quit = false;

    while( SDL_PollEvent( &keyPress ) != 0 )
    {
        if( keyPress.type == SDL_QUIT )
        {
            quit = true;
        }
    }

    return quit;
}
