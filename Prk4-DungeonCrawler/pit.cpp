#include "pit.h"
#include "ramp.h"

Pit::Pit(int row, int col):Tile("Pit", row, col)
{
}

string Pit::getTexture()
{
    return "Pit";
}

Tile* Pit::onEnter(Tile* fromTile, Character* who)
{
    if (typeid(*fromTile)==typeid(Ramp)||typeid(*fromTile)==typeid(Pit)){
        return this;
    }
    return nullptr;
}

Tile* Pit::onLeave(Tile* desTile, Character* who)
{
    if (typeid(*desTile)==typeid(Ramp)||typeid(*desTile)==typeid(Pit)){
        return this;
    }
    return nullptr;
}

Tile *Pit::CheckOnEnter(Tile *fromTile)
{
    if (typeid(*fromTile)==typeid(Ramp)||typeid(*fromTile)==typeid(Pit)){
        return this;
    }
    return nullptr;
}

Tile *Pit::CheckOnLeave(Tile *desTile)
{
    if (typeid(*desTile)==typeid(Ramp)||typeid(*desTile)==typeid(Pit)){
        return this;
    }
    return nullptr;
}
