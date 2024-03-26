#include "level.h"
#include "floor.h"
#include "player.h"
#include "wall.h"
#include "portal.h"
#include "door.h"
#include "switch.h"
#include "pit.h"
#include "ramp.h"
#include "levelchanger.h"
#include "chest.h"
#include "graphen.h"
#include "zombie.h"
#include "zombieattack.h"
#include "zombieguard.h"
#include <random>
#include <utility>

#include <iostream>

std::random_device dev;
std::mt19937 rd(dev());

Level::Level(string name, int hohe, int breite):Name(name), Hohe(hohe), Breite(breite), mustGraphreInit(true)
{
    Spielfeld.resize(Breite+2, vector<Tile*>(Hohe+2));

    for(int i=0; i < Hohe+2; i++){
        Spielfeld[0][i] = new Wall(0,i);
        Spielfeld[Breite+1][i] = new Wall(Breite+1,i);
    }
    for(int i=1; i <= Breite; i++){
        for (int j=1; j <= Hohe; j++){
            Spielfeld[i][j] = new Floor(i,j);
        }
    }

    for(int i=0; i < Breite+2; i++){
        Spielfeld[i][0] = new Wall(i,0);
        Spielfeld[i][Hohe+1] = new Wall(i, Hohe+1);
    }
    graphen = new Graphen();
}

Level::~Level()
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            delete Spielfeld[i][j];
        }
    }
    for (size_t i=0; i < characterlist.size(); i++){
        delete characterlist[i];
    }
    for (size_t i=0; i < portallist.size(); i++){
        delete portallist[i];
    }
    for (size_t i=0; i < doorlist.size(); i++){
        delete doorlist[i];
    }
    for (size_t i=0; i < switchlist.size(); i++){
        delete switchlist[i];
    }
}

Level::Level(const Level& l): Name(l.Name), Hohe(l.Hohe), Breite(l.Breite)
{
    Spielfeld = l.Spielfeld;
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            Tile* tile = l.getTile(i,j);
            if (typeid(*tile) == typeid(Floor)){
                auto f = dynamic_cast<Floor*>(tile);
                Spielfeld[i][j] = new Floor(*f);
            }
            if (typeid(*tile) == typeid(Wall)){
                auto w = dynamic_cast<Wall*>(tile);
                Spielfeld[i][j] = new Wall(*w);
            }
            if (typeid(*tile) == typeid(Portal)){
                auto p = dynamic_cast<Portal*>(tile);
                Spielfeld[i][j] = new Portal(*p);
            }
            if (typeid(*tile) == typeid(Door)){
                auto d = dynamic_cast<Door*>(tile);
                Spielfeld[i][j] = new Door(*d);
            }
            if (typeid(*tile) == typeid(Switch)){
                auto s = dynamic_cast<Switch*>(tile);
                Spielfeld[i][j] = new Switch(*s);
            }
            if (typeid(*tile) == typeid(Pit)){
                auto p = dynamic_cast<Pit*>(tile);
                Spielfeld[i][j] = new Pit(*p);
            }
            if (typeid(*tile) == typeid(Ramp)){
                auto r = dynamic_cast<Ramp*>(tile);
                Spielfeld[i][j] = new Ramp(*r);
            }
            if (typeid(*tile) == typeid(LevelChanger)){
                auto r = dynamic_cast<LevelChanger*>(tile);
                Spielfeld[i][j] = new LevelChanger(*r);
            }
            if (typeid(*tile) == typeid(Chest)){
                auto r = dynamic_cast<Chest*>(tile);
                Spielfeld[i][j] = new Chest(*r);
            }
        }
    }
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            Tile* tile = l.getTile(i,j);
            if (typeid(*tile) == typeid(Portal)){
                auto currTile = dynamic_cast<Portal*>(tile);
                int PortalType = currTile->getTypePortal();
                int row = currTile->getLinkPortal()->getRow();
                int col = currTile->getLinkPortal()->getCol();

                //attach destination point from copy to current field
                currTile = dynamic_cast<Portal*>(Spielfeld[i][j]);
                currTile->setPortalType(PortalType);
                auto currTileDes = dynamic_cast<Portal*>(Spielfeld[row][col]);
                currTile->setLinkPortal(currTileDes);
            }
            else if(typeid(*tile) == typeid(Switch))
            {
                auto currTile = dynamic_cast<Switch*>(tile);
                for(auto o : currTile->getPassiveObjects()){
                    Door* currDoor = dynamic_cast<Door*>(o);
                    int col = currDoor->getCol();
                    int row = currDoor->getRow();

                    //umlegen vom boinder :D
                    currDoor = dynamic_cast<Door*>(Spielfeld[row][col]);
                    auto currSwitch = dynamic_cast<Switch*>(Spielfeld[i][j]);
                    currSwitch->attach(currDoor);
                }
            }
        }
    }
}

Level& Level::operator=(Level l)
{
    std::swap(Spielfeld, l.Spielfeld);
    return *this;
}

int Level::getHohe() const
{
    return Hohe;
}

int Level::getBreite() const
{
    return Breite;
}

Character *Level::getChar(int pos)
{
    return characterlist[pos];
}

vector<Character *> Level::getCharacterlist()
{
    return characterlist;
}

Graphen *Level::getGraphen() const
{
    return graphen;
}

const string &Level::getName() const
{
    return Name;
}

const vector<vector<Tile *> > &Level::getSpielfeld() const
{
    return Spielfeld;
}

LevelChanger *Level::getLevelChanger1()
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(LevelChanger)){
                LevelChanger* s = dynamic_cast<LevelChanger*>(Spielfeld[i][j]);
                if(s->getLevelChangerType() == 1)
                    return s;
            }
        }
    }
    return nullptr;
}

LevelChanger *Level::getLevelChanger2()
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(LevelChanger)){
                LevelChanger* s = dynamic_cast<LevelChanger*>(Spielfeld[i][j]);
                if(s->getLevelChangerType() == 2)
                    return s;
            }
        }
    }
    return nullptr;
}

Tile *Level::findPlayerPosinList()
{
    for(auto c : characterlist){
        if(typeid(*c) == typeid(Player)){
            return c->getTile();
        }
    }
    return nullptr;
}

template <typename T>
void Level::eraseElement(vector<T *> &vec, int a)
{
    std::swap(vec[a], vec.back());
    vec.pop_back();
}

void Level::getAllPortal()
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (Spielfeld[i][j]->getTexture() == "Portal"){
                Portal* portal = dynamic_cast<Portal*>(Spielfeld[i][j]);
                if (portal->getLinkPortal() == nullptr){
                    portallist.push_back(portal);
                }
            }
        }
    }
}

void Level::connectPortal()
{
    std::uniform_int_distribution<int> num(0,2);
    this->getAllPortal();
    while (portallist.size()>1){
        std::uniform_int_distribution<int> dis(1,portallist.size()-1);
        int randNum = dis(rd);
        int typePortalNum = num(rd);
        portallist[0]->setLinkPortal(portallist[randNum]);
        portallist[randNum]->setLinkPortal(portallist[0]);
        portallist[0]->setPortalType(typePortalNum);
        portallist[randNum]->setPortalType(typePortalNum);
        eraseElement(portallist, randNum);
        eraseElement(portallist, 0);
    }
    if (portallist.size()==1){
        int row = portallist[0]->getRow();
        int col = portallist[0]->getCol();
        delete Spielfeld[row][col];
        eraseElement(portallist, 0);
        Spielfeld[row][col] = new Floor(row, col);
    }
}

void Level::getAllDoor()
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(Door)){
                Door* s = dynamic_cast<Door*>(Spielfeld[i][j]);
                doorlist.push_back(s);
            }
        }
    }
}
void Level::getAllSwitch()
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(Switch)){
                Switch* s = dynamic_cast<Switch*>(Spielfeld[i][j]);
                switchlist.push_back(s);
            }
        }
    }
}

void Level::connectDoor()
{
    getAllDoor();
    getAllSwitch();

    while ((switchlist.size() >=1) && (switchlist.size()>=1)){
        switchlist[0]->attach(doorlist[0]);
        eraseElement(switchlist, 0);
        eraseElement(doorlist, 0);
    }
}

Tile* Level::getTile(int row, int col)
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (Spielfeld[i][j]->isRightTile(row, col))
                return Spielfeld[i][j];
        }
    }
    return nullptr;
}

Tile* Level::getTile(int row, int col) const
{
    for(int i = 0; i < Breite+2; i++){
        for (int j = 0; j < Hohe+2; j++){
            if (Spielfeld[i][j]->isRightTile(row, col))
                return Spielfeld[i][j];
        }
    }
    return nullptr;
}

bool Level::checkCharacterinLevel()
{
    for(Character* c : characterlist){
        if(typeid(*c) == typeid(Player)){
            return true;
        }
    }
    return false;
}

bool Level::checkCharacterinList(Character *character)
{
    for(Character* c : characterlist){
        if(c == character){
            return false;
        }
    }
    characterlist.push_back(character);
    return true;
}

void Level::placeCharacter(Character* c, int row, int col)
{
    Tile* t1 = getTile(row, col);
    if ((t1->getTexture() == "Floor")or(t1->getTexture() == "Portal")){
        t1->setCharacter(c);
        c->setTile(t1);
        characterlist.push_back(c);
    }
}

void Level::randomPlayerpos(Character *character)
{
    int hohe, breite;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dis(0,fmin(Breite,Hohe-1));

    do{
        hohe = dis(mt);
        breite = dis(mt);
    }
    while((getTile(breite, hohe)->getTexture() != "Floor"));

    placeCharacter(character,breite,hohe);
}

bool Level::hasPlayerWin()
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(Chest)){
                Chest* s = dynamic_cast<Chest*>(Spielfeld[i][j]);
                return s->getHasWin();
            }
        }
    }
    return false;
}

bool Level::hasPlayerLose()
{
    for(auto character : characterlist){
        if(typeid(*character) == typeid(Player)){
            if(character->getisAlive()){
                return false;
            }
        }
    }
    return true;
}

void Level::eraseDeadCharacter()
{
    int index = -1;
    bool playerDead = false;
    for(size_t i = 0; i < characterlist.size(); i++)
    {
        if(!characterlist.at(i)->getisAlive())
        {
            index = i;
            playerDead = true;
        }
    }
    if(playerDead){
        characterlist.erase(characterlist.begin() + index);
    }

}

void Level::eraseCharacter(Character *character)
{
    int index = -1;
    bool foundCharacter = false;
    for(size_t i = 0; i < characterlist.size(); i++)
    {
        if(characterlist.at(i) == character)
        {
            index = i;
            foundCharacter = true;
        }
    }
    if(foundCharacter){
        characterlist.erase(characterlist.begin() + index);
    }
}

string Level::getPath(Tile *srcTile)
{
    if(mustGraphReInit()){
        graphen->initGraphen(this);
        setMustReInitGraph(false);
    }
    auto desTile = findPlayerPosinList();
    if(desTile == nullptr){
        return "s";
    }

    auto PathVector = graphen->shortestPathGraph(srcTile, desTile);
    string PathString;

    if(PathVector.size()==0){
        return "s";
    }
    for(int i=0; i < PathVector.size()-1; i++){
        int row = PathVector[i+1]->tile->getRow()-PathVector[i]->tile->getRow();
        int col = PathVector[i+1]->tile->getCol()-PathVector[i]->tile->getCol();
        if((row == -1) && (col == -1)){PathString += "q";}
        if((row == -1) && (col == 0)) {PathString += "w";}
        if((row == -1) && (col == 1)) {PathString += "e";}
        if((row == 0)  && (col == -1)){PathString += "a";}
        if((row == 0)  && (col == 0)) {PathString += "s";}
        if((row == 0)  && (col == 1)) {PathString += "d";}
        if((row == 1)  && (col == -1)){PathString += "z";}
        if((row == 1)  && (col == 0)) {PathString += "x";}
        if((row == 1)  && (col == 1)) {PathString += "c";}
    }
    return PathString;
}

bool Level::mustGraphReInit()
{
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(Door)){
                Door* d = dynamic_cast<Door*>(Spielfeld[i][j]);
                mustGraphreInit = d->getMustReInitGraph();
            }
        }
    }
    return mustGraphreInit;
}

void Level::setMustReInitGraph(bool newMustReInitGraph)
{
    mustGraphreInit = newMustReInitGraph;
    for(int i=0; i < Breite+2; i++){
        for (int j=0; j < Hohe+2;j++){
            if (typeid(*Spielfeld[i][j]) == typeid(Door)){
                Door* d = dynamic_cast<Door*>(Spielfeld[i][j]);
                d->setMustReInitGraph(newMustReInitGraph);
            }
        }
    }
}

void Level::placeWall(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Wall(row,col);
}

void Level::placePortal(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Portal(row,col);
}

void Level::PlacePortalwithType(int row, int col, int typePortal)
{
    delete Spielfeld[row][col];
    auto portal = new Portal(row,col);
    portal->setPortalType(typePortal);
    Spielfeld[row][col] = portal;
}

void Level::placeDoor(int row, int col, bool isOpen)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Door(row,col,isOpen);
}

void Level::placeSwitch(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Switch(row,col);
}

void Level::placePit(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Pit(row,col);
}

void Level::placeRamp(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Ramp(row,col);
}

void Level::placeLevelChanger(int row, int col, int type)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new LevelChanger(row,col,type);
}

void Level::placeChest(int row, int col)
{
    delete Spielfeld[row][col];
    Spielfeld[row][col] = new Chest(row,col);
}

void Level::placePlayer(Character *player, int row, int col, int strength, int stamina, int hitpoints)
{
    player->setStrength(strength);
    player->setHitpoints(hitpoints);
    player->setStamina(stamina);
    placeCharacter(player,row,col);
}

void Level::placeZombie(int row, int col, int strength, int stamina)
{
    placeCharacter(new Zombie(strength,stamina),row,col);
}

void Level::placeZombieGuard(int row, int col, int strength, int stamina, int lastMove, std::string Muster)
{
    auto newZombie = new ZombieGuard(strength,stamina, Muster);
    newZombie->setLastMove(lastMove);
    placeCharacter(newZombie,row,col);
}

void Level::placeZombieAttack(int row, int col, int strength, int stamina)
{
    placeCharacter(new ZombieAttack(strength,stamina),row,col);
}

void Level::Link2Portal(int row, int col, int linkRow, int LinkCol)
{
    auto tile = getTile(row,col);
    auto linktile = getTile(linkRow,LinkCol);
    auto portal = dynamic_cast<Portal*>(tile);
    auto linkPortal = dynamic_cast<Portal*>(linktile);
    portal->setLinkPortal(linkPortal);
    linkPortal->setLinkPortal(portal);
}

void Level::attachDoorToSwitch(int SwitchRow, int SwitchCol, int DoorRow, int DoorCol)
{
    auto tile = getTile(SwitchRow,SwitchCol);
    auto linktile = getTile(DoorRow,DoorCol);
    auto switchTile = dynamic_cast<Switch*>(tile);
    auto doorTile = dynamic_cast<Door*>(linktile);
    switchTile->attach(doorTile);
}

