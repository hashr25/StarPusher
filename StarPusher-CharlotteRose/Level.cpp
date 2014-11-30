#include "Level.h"

///Constructor and destructors
Level::Level()
{
    clear();
}

///Getters and Setters
//Getters
Tile** Level::getTiles() { return tiles; }
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
void Level::setTiles( Tile** tiles ) { this -> tiles = tiles; }
void Level::setStars( std::vector<Star> stars ) { this -> stars = stars; }
void Level::setTotalTiles( int totalTiles ) { this -> totalTiles = totalTiles; }
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
    delete tiles;
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
