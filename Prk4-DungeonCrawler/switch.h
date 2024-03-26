#ifndef Switch_h
#define Switch_h

#include "active.h"
#include "tile.h"

using std::string;

class Switch: public Tile, public Active
{
public:
    Switch(int row, int col);

    string getTexture() override;
    Tile* onEnter(Tile* fromTile, Character* who) override;

    vector<Passive*> getPassiveObjects();

    Tile* CheckOnEnter(Tile* fromTile) override;
};

#endif
