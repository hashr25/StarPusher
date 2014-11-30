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

//Camera movement
///number is pixels per second
const int CAMERA_SPEED = 10;

enum Direction
{
    NO_MOVE,        //0
    NORTH,          //1
    EAST,           //2
    SOUTH,          //3
    WEST            //4
};

enum TileType
{
    NO_TYPE,        //0
    BOY,            //1
    CAT_GIRL,       //2
    HORN_GIRL,      //3
    PINK_GIRL,      //4
    PRINCESS,       //5
    STAR,           //6
    ON_GOAL,        //7
    OFF_GOAL,       //8
    FLOOR,          //9
    WALL,           //10
    CORNER,         //11
    GRASS,          //12
    ROCK,           //13
    SHORT_TREE,     //14
    TALL_TREE,      //15
    UGLY_TREE,      //16
    TOTAL_TEXTURES  //17
};

#endif // ENUMTYPES_H
