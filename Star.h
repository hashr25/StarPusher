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
    SDL_Rect getStarRect() const;
    // Setters
    void setIsAtGoal( bool isAtGoal );
    void setTopLeft( int x, int y );

    /// Methods
    bool isBlocked( Direction directionToCheck );
    void push( Direction directionToPush );

private:
    bool isAtGoal;

<<<<<<< HEAD
    SDL_Rect mBox;
=======
    int x;
    int y;
>>>>>>> master

};

#endif // STAR_H_INCLUDED

