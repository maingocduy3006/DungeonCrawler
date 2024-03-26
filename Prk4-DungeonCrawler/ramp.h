#ifndef Ramp_h
#define Ramp_h

#include "tile.h"

class Ramp: public Tile
{
public:
    Ramp(int row, int col);
    string getTexture() override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* CheckOnEnter(Tile* fromTile) override;
};

#endif
