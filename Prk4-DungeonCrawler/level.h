#ifndef Level_h
#define Level_h

#include <stdio.h>
#include <array>
#include <vector>
#include "tile.h"
#include "character.h"

using std::array;
using std::vector;

class Floor;
class Wall;
class Portal;
class Door;
class Switch;
class LevelChanger;
class Graphen;

class Level
{
private:
    const string Name;
    const int Hohe;
    const int Breite;
    vector<vector<Tile*>> Spielfeld;
    Graphen* graphen;
    bool mustGraphreInit;

    vector<Portal*> portallist;
    vector<Switch*> switchlist;
    vector<Door*> doorlist;
    vector<Character*> characterlist;

public:
    Level(string name, int hohe, int breite);
    ~Level();
    Level(const Level& l);
    Level& operator=(Level l);

    int getHohe() const;
    int getBreite() const;
    Character* getChar(int pos);
    vector<Character *> getCharacterlist();
    Graphen *getGraphen() const;
    const vector<vector<Tile *> > &getSpielfeld() const;
    const string &getName() const;
    LevelChanger* getLevelChanger1();
    LevelChanger* getLevelChanger2();

    Tile* findPlayerPosinList();

    template <typename T>
    void eraseElement(vector<T*>& vec, int a);

    void getAllPortal();
    void connectPortal();

    void getAllDoor();
    void getAllSwitch();
    void connectDoor();

    Tile* getTile(int row, int col);
    Tile* getTile(int row, int col) const;

    bool checkCharacterinLevel();
    bool checkCharacterinList(Character* character);
    void placeCharacter(Character* c, int row, int col);
    void randomPlayerpos(Character* character);

    bool hasPlayerWin();
    bool hasPlayerLose();

    void eraseDeadCharacter();
    void eraseCharacter(Character* character);

    string getPath(Tile* srcTile);

    bool mustGraphReInit();
    void setMustReInitGraph(bool newMustReInitGraph);

    void placeWall(int row, int col);
    void placePortal(int row, int col);
    void PlacePortalwithType(int,int,int);
    void placeDoor(int row, int col, bool isOpen);
    void placeSwitch(int row, int col);
    void placePit(int row, int col);
    void placeRamp(int row, int col);
    void placeLevelChanger(int row, int col,int type);
    void placeChest(int row, int col);

    void placePlayer(Character*,int, int, int, int, int);
    void placeZombie(int,int,int,int);
    void placeZombieGuard(int,int,int,int, int lastMove, string Muster);
    void placeZombieAttack(int,int,int,int);

    void Link2Portal(int,int,int,int);
    void attachDoorToSwitch(int,int,int,int);
    friend class TerminalUI;
};

#endif
