#ifndef ENUMTYPES_H
#define ENUMTYPES_H

//The dimensions of the dot
static const int PLAYER_WIDTH = 20;
static const int PLAYER_HEIGHT = 20;

//Maximum axis velocity of the dot
static const int PLAYER_VEL = 10;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

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
    PLAYER,
    STAR,
    GOAL,
    FLOOR,
    WALL,
    DECORATION,
    TOTAL_TILES_NUMBER
};

enum TextureName
{
    PLAYER_IMG,
    STAR_IMG,
    OFF_GOAL_IMG,
    ON_GOAL_IMG,
    FLOOR_IMG,
    WALL_IMG,
    CORNER_IMG,
    GRASS_IMG,
    SHORT_TREE_IMG,
    TALL_TREE_IMG,
    UGLY_TREE_IMG,
    ROCK_IMG,
    SOLVED_IMG,
    TITLE_SCREEN_IMG,
    TOTAL_TEXTURES
};

#endif // ENUMTYPES_H
