#ifndef ENUMTYPES_H
#define ENUMTYPES_H

//The dimensions of the dot
static const int PLAYER_WIDTH = 50;
static const int PLAYER_HEIGHT = 85;

//Maximum axis velocity of the dot
static const int PLAYER_VEL = 15;

//The dimensions of the level
const int LEVEL_WIDTH = 450;
const int LEVEL_HEIGHT = 405;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Tile constants
const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 85;
const int TILE_FLOOR_HEIGHT = 40;
const int TOTAL_TILES = 81;

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
    BOY_IMG,
    CAT_GIRL_IMG,
    HORN_GIRL_IMG,
    PINK_GIRL_IMG,
    PRINCESS_IMG,
    STAR_IMG,
    ON_GOAL_IMG,
    OFF_GOAL_IMG,
    FLOOR_IMG,
    WALL_IMG,
    CORNER_IMG,
    GRASS_IMG,
    ROCK_IMG,
    SHORT_TREE_IMG,
    TALL_TREE_IMG,
    UGLY_TREE_IMG,
    TOTAL_TEXTURES
};

#endif // ENUMTYPES_H
