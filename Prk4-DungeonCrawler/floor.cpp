#include <stdio.h>
#include "floor.h"

Floor::Floor(int row, int col):Tile("Floor", row, col)
{
}

string Floor::getTexture()
{
    return "Floor";
}

Tile* Floor::onEnter(Tile *fromTile, Character *who)
{
    return this;
}

Tile *Floor::onLeave(Tile *desTile, Character *who)
{
    return this;
}

Tile *Floor::CheckOnEnter(Tile *fromTile)
{
    return this;
}

Tile *Floor::CheckOnLeave(Tile *desTile)
{
    return this;
}
