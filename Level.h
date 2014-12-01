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
<<<<<<< HEAD
    ~Level();

    ///Getters and Setters
    //Getters
    std::vector<Tile*> getTiles();
=======

    ///Getters and Setters
    //Getters
    Tile** getTiles();
>>>>>>> origin/CharlotteRose
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
<<<<<<< HEAD
    void setTiles( std::vector<Tile*> tiles );
    void setStars( std::vector<Star> stars );
    void setTotalTiles( int totalTiles );
    void setTotalTiles();
=======
    void setTiles( Tile** tiles );
    void setStars( std::vector<Star> stars );
    void setTotalTiles( int totalTiles );
>>>>>>> origin/CharlotteRose
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

<<<<<<< HEAD
    void addTile( Tile* tile );

private:
    std::vector<Tile*> tiles;
=======
    ///Public Data for Now
    Tile** tiles;

private:
>>>>>>> origin/CharlotteRose
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
