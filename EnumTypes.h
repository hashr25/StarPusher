#ifndef ENUMTYPES_H
#define ENUMTYPES_H

//The dimensions of the player
static const int PLAYER_WIDTH = 50;
static const int PLAYER_HEIGHT = 85;

//The dimensions of the test level
const int LEVEL_WIDTH = 750;
const int LEVEL_HEIGHT = 675;

//The dimensions of the game window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Tile constants
const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 85;
const int TILE_FLOOR_HEIGHT = 40;
const int TOTAL_TILES = 15*15;

enum Direction
{
    NO_MOVE,
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum TileType
{
    NO_TYPE,
    BOY,
    CAT_GIRL,
    HORN_GIRL,
    PINK_GIRL,
    PRINCESS,
    STAR,
    ON_GOAL,
    OFF_GOAL,
    FLOOR,
    WALL,
    CORNER,
    GRASS,
    ROCK,
    SHORT_TREE,
    TALL_TREE,
    UGLY_TREE,
    TOTAL_TEXTURES
};

#endif // ENUMTYPES_H
