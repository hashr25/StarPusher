#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "Tile.h"
#include "Star.h"

class Level
{
public:
    ///Constructor and destructors
    Level();

    ///Getters and Setters
    //Getters
    Tile** getTiles();
    std::vector<Star> getStars();
    int getTotalTiles();
    int getNumberOfStars();
    int getPlayerX();
    int getPlayerY();
    int getLevelHeightInTiles();
    int getLevelWidthInTiles();
    int getLevelHeightInPixels();
    int getLevelWidthInPixels();

    //Setters
    void setTiles( Tile** tiles );
    void setStars( std::vector<Star> stars );
    void setTotalTiles( int totalTiles );
    void setNumberOfStars( int numberOfStars );
    void setPlayerX( int playerStartX );
    void setPlayerY( int playerStartY );
    void setLevelHeightInTiles( int levelHeightInTiles );
    void setLevelWidthInTiles( int levelWidthInTiles );
    void setLevelHeightInPixels( int levelHeightInPixels );
    void setLevelWidthInPixels( int levelWidthInPixels );

    ///Methods
    void clear();
    void addStar( Star newStar );

    ///Public Data for Now
    Tile** tiles;

private:
    std::vector<Star> stars;

    int totalTiles;
    int numberOfStars;

    int playerStartX;
    int playerStartY;

    int levelHeightInTiles;
    int levelWidthInTiles;

    int levelHeightInPixels;
    int levelWidthInPixels;
};

#endif // LEVEL_H
