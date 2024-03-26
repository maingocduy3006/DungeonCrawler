#ifndef Door_h
#define Door_h

#include "passive.h"
#include "floor.h"
#include "wall.h"

class Door: public Floor, public Wall, public Passive
{
private:
    bool isOpen;
    bool mustReInitGraph;
public:
    Door(int row, int col);
    Door(int row, int col, bool isopen);
    bool getisOpend();
    void notify(Active* source) override;
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* desTile, Character* who) override;
    string getTexture() override;
    bool getMustReInitGraph() const;
    void setMustReInitGraph(bool newMustReInitGraph);

    Tile* CheckOnEnter(Tile* fromTile) override;
    Tile* CheckOnLeave(Tile* desTile) override;
};

#endif
