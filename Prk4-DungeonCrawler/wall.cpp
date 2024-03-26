#include <stdio.h>
#include "wall.h"

Wall::Wall(int row, int col): Tile("Wall", row, col)
{
}

string Wall::getTexture()
{
    return "Wall";
}

Tile* Wall::onEnter(Tile *fromTile, Character *who)
{
    return nullptr;
}

Tile *Wall::onLeave(Tile *desTile, Character *who)
{
    return nullptr;
}

Tile *Wall::CheckOnEnter(Tile *fromTile)
{
    return nullptr;
}

Tile *Wall::CheckOnLeave(Tile *desTile)
{
    return nullptr;
}
