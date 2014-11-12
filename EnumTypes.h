#ifndef ENUMTYPES_H
#define ENUMTYPES_H

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
    GRASS,
    TOTAL_TILES
};

enum TextureName
{
    GRASS_IMG,
    PLAYER_IMG,
    TOTAL_TEXTURES
};

#endif // ENUMTYPES_H
