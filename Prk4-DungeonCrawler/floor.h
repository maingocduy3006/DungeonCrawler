#ifndef Floor_h
#define Floor_h

#include "tile.h"

class Floor: virtual public Tile
{
public:
    Floor(int row, int col);
    string getTexture() override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* desTile, Character* who) override;

    Tile* CheckOnEnter(Tile* fromTile) override;
    Tile* CheckOnLeave(Tile* desTile) override;
};

#endif /* Floor_h */
