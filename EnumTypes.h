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
    OTHER
};

#endif // ENUMTYPES_H
