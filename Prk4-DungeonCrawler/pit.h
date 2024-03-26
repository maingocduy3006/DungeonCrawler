#ifndef Pit_h
#define Pit_h

#include "tile.h"

class Pit: public Tile
{
public:
    Pit(int row, int col);
    string getTexture() override;

    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* desTile, Character* who) override;

    Tile* CheckOnEnter(Tile* fromTile) override;
    Tile* CheckOnLeave(Tile* desTile) override;
};

#endif
