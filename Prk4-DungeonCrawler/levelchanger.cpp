#include "levelchanger.h"
#include "level.h"

LevelChanger::LevelChanger(int row, int col, int lvlChangerType): Tile("Levelchanger",row, col), Active(), levelChangerType(lvlChangerType)
{
}

string LevelChanger::getTexture()
{
    return "Levelchanger";
}

Level *LevelChanger::getLevel()
{
    return level;
}

LevelChanger *LevelChanger::getLevelChanger()
{
    return linkLevelChanger;
}

int LevelChanger::getLevelChangerType()
{
    return levelChangerType;
}

LevelChanger *LevelChanger::getLinkLevelChanger() const
{
    return linkLevelChanger;
}

void LevelChanger::setLevel(Level *lvl)
{
    level = lvl;
}

void LevelChanger::setLinkLevelChanger(LevelChanger *lvlChanger)
{
    linkLevelChanger = lvlChanger;
}

Tile *LevelChanger::onEnter(Tile *fromTile, Character *who)
{
    this->activate();
    return linkLevelChanger;
}

Tile *LevelChanger::CheckOnEnter(Tile *fromTile)
{
    return linkLevelChanger;
}
