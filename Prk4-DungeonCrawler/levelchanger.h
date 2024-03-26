#ifndef LEVELCHANGER_H
#define LEVELCHANGER_H

#include "tile.h"
#include "active.h"

class Level;
class LevelChanger: public Tile, public Active
{
private:
    int levelChangerType;
    Level* level;
    LevelChanger* linkLevelChanger;
public:
    LevelChanger(int row, int col, int lvlChangerType);

    string getTexture() override;
    Level* getLevel();
    LevelChanger* getLevelChanger();
    int getLevelChangerType();
    LevelChanger *getLinkLevelChanger() const;

    void setLevel(Level* lvl);
    void setLinkLevelChanger(LevelChanger* lvlChanger);

    Tile* onEnter(Tile* fromTile, Character* who) override;

    Tile* CheckOnEnter(Tile* fromTile) override;
};

#endif // LEVELCHANGER_H
