#include "ramp.h"

Ramp::Ramp(int row, int col) : Tile("Ramp", row, col)
{
}

string Ramp::getTexture()
{
    return "Ramp";
}

Tile* Ramp::onEnter(Tile* fromTile, Character* who)
{
    return this;
}

Tile *Ramp::CheckOnEnter(Tile *fromTile)
{
    return this;
}
