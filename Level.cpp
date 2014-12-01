#include "Level.h"

///Constructor and destructors
Level::Level()
{
    clear();
}

<<<<<<< HEAD
Level::~Level()
{
    for( int i = 0; i < tiles.size(); i++ )
    {
        delete tiles[i];
    }
    clear();
}

///Getters and Setters
//Getters
std::vector<Tile*> Level::getTiles() { return tiles; }
=======
///Getters and Setters
//Getters
Tile** Level::getTiles() { return tiles; }
>>>>>>> origin/CharlotteRose
std::vector<Star> Level::getStars() { return stars; }
int Level::getTotalTiles() { return totalTiles; }
int Level::getNumberOfStars() { return numberOfStars; }
int Level::getPlayerX() { return playerStartX; }
int Level::getPlayerY() { return playerStartY; }
int Level::getLevelHeightInTiles() { return levelHeightInTiles; }
int Level::getLevelWidthInTiles() { return levelWidthInTiles; }
int Level::getLevelHeightInPixels() { return levelHeightInPixels; }
int Level::getLevelWidthInPixels() { return levelWidthInPixels; }

//Setters
<<<<<<< HEAD
void Level::setTiles( std::vector<Tile*> tiles ) { this -> tiles = tiles; }
void Level::setStars( std::vector<Star> stars ) { this -> stars = stars; }
void Level::setTotalTiles( int totalTiles ) { this -> totalTiles = totalTiles; }
void Level::setTotalTiles() { totalTiles = levelWidthInTiles * levelHeightInTiles; }
=======
void Level::setTiles( Tile** tiles ) { this -> tiles = tiles; }
void Level::setStars( std::vector<Star> stars ) { this -> stars = stars; }
void Level::setTotalTiles( int totalTiles ) { this -> totalTiles = totalTiles; }
>>>>>>> origin/CharlotteRose
void Level::setNumberOfStars( int numberOfStars ) { this -> numberOfStars = numberOfStars; }
void Level::setPlayerX( int playerStartX ) { this -> playerStartX = playerStartX; }
void Level::setPlayerY( int playerStartY ) { this -> playerStartY = playerStartY; }
void Level::setLevelHeightInTiles( int levelHeightInTiles ) { this -> levelHeightInTiles = levelHeightInTiles; }
void Level::setLevelWidthInTiles( int levelWidthInTiles ) { this -> levelWidthInTiles = levelWidthInTiles; }
void Level::setLevelHeightInPixels( int levelHeightInPixels ) { this -> levelHeightInPixels = levelHeightInPixels; }
void Level::setLevelWidthInPixels( int levelWidthInPixels ) { this -> levelWidthInPixels = levelWidthInPixels; }

///Methods
void Level::clear()
{
<<<<<<< HEAD
    tiles.clear();
=======
    delete tiles;
>>>>>>> origin/CharlotteRose
    stars.clear();
    totalTiles = 0;
    playerStartX = 0;
    playerStartY = 0;
    levelHeightInTiles = 0;
    levelWidthInTiles = 0;
    levelHeightInPixels = 0;
    levelWidthInPixels = 0;
}

void Level::addStar( Star newStar )
{
    stars.push_back( newStar );
}
<<<<<<< HEAD

void Level::addTile( Tile* tile )
{
    tiles.push_back( tile );
}
=======
>>>>>>> origin/CharlotteRose
