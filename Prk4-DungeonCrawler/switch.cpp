#include "switch.h"

Switch::Switch(int row, int col): Tile("Switch", row, col), Active()
{
}

string Switch::getTexture()
{
    return "Switch";
}

Tile* Switch::onEnter(Tile* fromTile, Character* who)
{
    this->activate();
    return this;
}

vector<Passive*> Switch::getPassiveObjects()
{
    return passivListe;
}

Tile *Switch::CheckOnEnter(Tile *fromTile)
{
    return this;
}
