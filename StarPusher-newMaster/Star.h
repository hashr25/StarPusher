#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

#include "Tile.h"
#include "EnumTypes.h"
class Star
{
public:

    /// Constructors
    Star();
    Star( int x, int y );

    /// Getters and Setters
    // Getters
    bool getIsAtGoal() const;
    int getX() const;
    int getY() const;
    // Setters
    void setIsAtGoal( bool isAtGoal );
    void setNewPos( int x, int y );

    /// Methods
    bool isBlocked( Direction directionToCheck );
    void push( Direction directionToPush );

//    bool touchesWall(Level gameLevels, int currentLevel, int x, int y);
    bool checkCollision( SDL_Rect a, SDL_Rect b );
    void render( SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect gTileClips[ TOTAL_TYPES ], LTexture& gTileTexture );

private:
    bool isAtGoal;

    int x;
    int y;
};

#endif // STAR_H_INCLUDED

