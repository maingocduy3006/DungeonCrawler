#include "chest.h"

Chest::Chest(int row, int col): Tile("Chest", row, col), hasWin(false)
{

}

string Chest::getTexture()
{
    return "Chest";
}

Tile *Chest::onEnter(Tile *fromTile, Character *who)
{
    hasWin = true;
    return this;
}

bool Chest::getHasWin() const
{
    return hasWin;
}

Tile *Chest::CheckOnEnter(Tile *fromTile)
{
    return this;
}

