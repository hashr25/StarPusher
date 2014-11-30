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
    // Setters
    void setIsAtGoal( bool isAtGoal );

    /// Methods
    bool isBlocked( Direction directionToCheck );
    void push( Direction directionToPush );

private:
    bool isAtGoal;

    int x;
    int y;

};

#endif // STAR_H_INCLUDED

