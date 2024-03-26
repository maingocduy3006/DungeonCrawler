#ifndef DungeonCrawler_h
#define DungeonCrawler_h

#include <stdio.h>
#include "level.h"
#include "abstraktui.h"
#include "list.h"
#include "passive.h"
#include "player.h"
class TerminalUI;
class Controller;
class GraphicalUI;
class DungeonCrawler: public Passive
{
public:

private:
    AbstraktUI* abstraktUI;
    Level* level;
    List level_list;
    List::iterator iterator;
    GraphicalUI* grapUI;
    bool isChangedLevel;
public:
    DungeonCrawler();
    void play();
    Level* getLevel();
    void notify(Active* source) override;

    void connectLevel();
    void initLevelList(Character* character);
    bool getIsChangedLevel() const;
    void setIsChangedLevel(bool newIsChangedLevel);

    bool ReadFile(string path, Player* character);
    void WriteFile(string path);

    bool LoadSaveFile(string path, Player* character);

    int countConnections(Level* lvl);

    size_t getLevelListSize();
};
#endif /* DungeonCrawler_hpp */
