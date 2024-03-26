#ifndef CHEST_H
#define CHEST_H

#include "tile.h"

class Chest: public Tile
{
public:
    Chest(int row, int col);
    string getTexture() override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
    bool getHasWin() const;

    Tile* CheckOnEnter(Tile* fromTile) override;
private:
    bool hasWin;
};

#endif // CHEST_H
