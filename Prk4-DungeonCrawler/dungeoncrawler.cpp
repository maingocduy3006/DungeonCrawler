#include "dungeoncrawler.h"
#include "door.h"
#include "graphen.h"
#include "levelchanger.h"
#include "player.h"
#include "portal.h"
#include "switch.h"
#include "terminalui.h"
#include "controller.h"
#include "graphicalui.h"
#include "zombie.h"
#include "zombieattack.h"
#include "zombieguard.h"
//#include <json/value.h>
//#include <jsoncpp/json/json.h>
#include <random>
#include <iostream>
#include <fstream>
#include <QDebug>

using namespace std;

DungeonCrawler::DungeonCrawler():
    Passive(),
    abstraktUI(nullptr),
    level(nullptr),
    iterator(NULL),
    isChangedLevel(false)
{
}

void DungeonCrawler::play()
{
    //level = new Level();
    //TerminalUI* terminalUI = new TerminalUI();
    string path = "/Users/hoanh139/desktop/Praktikum4";
    Player *character = new Player(grapUI, 100,100);
    //Character *character = new Player(terminalUI, 100,100);
    initLevelList(character);
    connectLevel();
    iterator = level_list.begin();
    level = *iterator;
    grapUI = new GraphicalUI(this, "//Users/hoanh139/desktop/Praktikum4");
    character->setController(grapUI);
    abstraktUI = grapUI;
    abstraktUI->draw(level);
    WriteFile(path + "/leveldatei.txt");
    //abstraktUI=terminalUI;

    if(grapUI->start()){
        LoadSaveFile(path + "/levelsavedatei.txt",character);
        connectLevel();
    }

    while (true){
        if(isChangedLevel){
            level = *iterator;
        }
        if(grapUI->checkIfGameEnd(level)){
            return;
        }
        abstraktUI->draw(level);
        auto characterList = level->getCharacterlist();

        for(size_t i=0; i<characterList.size(); i++){
            Tile* currTile = characterList[i]->getTile();
            int charRow = currTile->getRow();
            int charCol = currTile->getCol();
            char charMove = characterList[i]->move(level);
            switch (charMove){
            case 'q': charRow--; charCol--; break;
            case 'w': charRow--;            break;
            case 'e': charRow--; charCol++; break;
            case 'a':            charCol--; break;
            case 's':                       break;
            case 'd':            charCol++; break;
            case 'z': charRow++; charCol--; break;
            case 'x': charRow++;            break;
            case 'c': charRow++; charCol++; break;
            }
            if(!currTile->moveTo(level->getTile(charRow, charCol),characterList[i])){
                cout<<"Blocked"<<endl;
            }
            level->eraseDeadCharacter();
        }
    }
}

Level *DungeonCrawler::getLevel()
{
    return level;
}

bool DungeonCrawler::getIsChangedLevel() const
{
    return isChangedLevel;
}

void DungeonCrawler::setIsChangedLevel(bool newIsChangedLevel)
{
    isChangedLevel = newIsChangedLevel;
}

void DungeonCrawler::notify(Active *source)
{
    LevelChanger* lvlchanger = static_cast<LevelChanger*>(source);
    auto& oldLvl = *iterator;
    if(lvlchanger->getLevelChangerType()==1){
        --iterator;
    }
    else{
        ++iterator;
    }

    for(auto& character : oldLvl->getCharacterlist()){
        if(dynamic_cast<GraphicalUI*>(character->getController()) == dynamic_cast<GraphicalUI*>(abstraktUI)){
            auto newLvl = *iterator;
            newLvl->checkCharacterinList(character);
            oldLvl->eraseCharacter(character);
        }
    }
    isChangedLevel=true;
}

void DungeonCrawler::connectLevel()
{
    List::iterator it1 = level_list.begin();
    while(it1.getNextLevel() != nullptr){
        auto lvc1 = (*it1)->getLevelChanger2();
        auto lvc2 = (it1.getNextLevel())->getLevelChanger1();
        if(lvc1&&lvc2){
            lvc1->setLevel(*it1);
            lvc1->setLinkLevelChanger(lvc2);
            lvc2->setLevel(it1.getNextLevel());
            lvc2->setLinkLevelChanger(lvc1);
            lvc1->attach(this);
            lvc2->attach(this);
        }
        ++it1;
    }
}

void DungeonCrawler::initLevelList(Character *character)
{
    int AnzahlLevel = 3;
    for (int i=0; i<AnzahlLevel; i++){
        if (i==0){
            Level* tmp = new Level("Level_1",6,3);
            for(int j=1; j<7;j++){
                tmp->placeWall(2,j);
            }
            tmp->placePortal(1,6);
            tmp->placePortal(3,1);
            tmp->placeLevelChanger(3,6,2);
            tmp->placeCharacter(character,1,1);
            tmp->connectPortal();
            level_list.push_back(tmp);
        }
        else if(i==1){
            Level* tmp = new Level("Level_2",6,6);
            for(int j=3; j<7;j++){
                tmp->placeWall(5,j);
            }
            Character *zombie = new Zombie(20,1000);
            Character *attackzombie = new ZombieAttack(20,100);
            tmp->placeCharacter(zombie,2,2);
            tmp->placeCharacter(attackzombie,1,2);
            tmp->placePortal(1,6);
            tmp->placePortal(1,1);
            tmp->placeLevelChanger(2,1,2);
            tmp->placeLevelChanger(6,1,1);
            tmp->placePit(1,4);
            for(int j=3; j<6;j++){
                tmp->placePit(j,1);
                tmp->placePit(j,2);
            }
            for(int j=4; j<7;j++){
                tmp->placePit(2,j);
                tmp->placePit(3,j);
            }
            tmp->placeRamp(1,5);
            tmp->placeRamp(4,5);
            for(int j=1; j<6;j++){
                tmp->placeWall(j,3);
            }
            tmp->placeDoor(5,4,false);
            tmp->placeSwitch(6,6);
            tmp->connectPortal();
            tmp->connectDoor();
            level_list.push_back(tmp);
        }
        else if(i==2){
            Level* tmp = new Level("Level_3",10,10);
            Character *zombie1 = new Zombie(20,100);
            Character *zombie2 = new ZombieGuard(20,100,"ddaaaadd");
            tmp->placeCharacter(zombie1,4,4);
            tmp->placeCharacter(zombie2,6,6);
            tmp->placeLevelChanger(1,1,1);
            tmp->placeChest(9,9);
            level_list.push_back(tmp);
        }
    }
}

bool DungeonCrawler::ReadFile(std::string path, Player *character)
{
    ifstream source(path);

    if(!source.good()){
        std::cerr << path << " kann nicht geÃ¶ffnet werden!\n";
        return false;
    }
    char peeky = source.peek();
    if(peeky == EOF){
        return false;
    }

    string line;
    getline(source, line);
    getline(source, line, ':');

    source.get();
    int numberOfLevels;
    source >> numberOfLevels;
    source.get();
    for(int i=0; i<numberOfLevels; i++){
        getline(source, line);
        getline(source, line, ' ');
        //source.get();
        getline(source, line, ':');
        string LevelName(line);

        getline(source, line, ':');
        source.get();
        int Breite;
        source >> Breite;

        getline(source, line, ':');
        source.get();
        int Hohe;
        source >> Hohe;

        Level* newLevel = new Level(LevelName,Hohe,Breite);

        getline(source, line);

        for(int i=0; i< Breite*Hohe; i++){
            getline(source, line, ' ');
            getline(source, line);
            string tileTexture(line);

            if(tileTexture == "Floor"){
                getline(source, line);
                getline(source, line);
                continue;
            }
            else if(tileTexture == "Wall"){
                getline(source, line, ':');
                source.get();
                int row;
                source >> row;
                getline(source, line, ':');
                source.get();
                int col;
                source >> col;
                newLevel->placeWall(row,col);
                getline(source, line);
            }
            else if(tileTexture == "Portal"){
                string e = line;
                getline(source, line, ':');
                string f = line;
                source.get();
                int row;
                source >> row;
                string a = line;
                getline(source, line, ':');
                string m = line;
                source.get();
                int col;
                source >> col;
                string d = line;
                getline(source, line, ':');
                string c = line;
                source.get();
                int type;
                source >> type;
                string n = line;
                newLevel->PlacePortalwithType(row,col,type);
                getline(source, line);
            }
            else if(tileTexture == "Switch"){
                getline(source, line, ':');
                source.get();
                int row;
                source >> row;
                getline(source, line, ':');
                source.get();
                int col;
                source >> col;
                newLevel->placeSwitch(row,col);
                getline(source, line);
            }
            else if(tileTexture == "OpenDoor"||tileTexture == "CloseDoor"){
                getline(source, line, ':');
                source.get();
                int row;
                source >> row;
                getline(source, line, ':');
                source.get();
                int col;
                source >> col;
                getline(source, line, ':');
                source.get();
                bool status;
                source >> status;
                newLevel->placeDoor(row,col,status);
                getline(source, line);
            }
            else if(tileTexture == "Ramp"){
                getline(source, line, ':');
                source.get();
                int row;
                source >> row;
                getline(source, line, ':');
                source.get();
                int col;
                source >> col;
                newLevel->placeRamp(row,col);
                getline(source, line);
            }
            else if(tileTexture == "Pit"){
                getline(source, line, ':');
                source.get();
                int row;
                source >> row;
                getline(source, line, ':');
                source.get();
                int col;
                source >> col;
                newLevel->placePit(row,col);
                getline(source, line);
            }
            else if(tileTexture == "Levelchanger"){
                getline(source, line, ':');
                source.get();
                int row;
                source >> row;
                getline(source, line, ':');
                source.get();
                int col;
                source >> col;
                getline(source, line, ':');
                source.get();
                int typeLV;
                source >> typeLV;
                newLevel->placeLevelChanger(row,col,typeLV);
                getline(source, line);
            }
            else if(tileTexture == "Chest"){
                getline(source, line, ':');
                source.get();
                int row;
                source >> row;
                getline(source, line, ':');
                source.get();
                int col;
                source >> col;
                newLevel->placeChest(row,col);
                getline(source, line);
            }
        }
        string A = line;
        getline(source, line);
        string b = line;
        //getline(source, line);
        string c = line;
        getline(source, line, ':');
        string d = line;
        source.get();
        int numberCharacter;
        source >> numberCharacter;

        for(int i=0; i<numberCharacter;i++){
            getline(source, line, ' ');
            getline(source, line);
            string playerTexture(line);
            if(playerTexture == "Player"){
                getline(source, line, ':');
                source.get();
                int currRow;
                source >> currRow;
                getline(source, line, ':');
                source.get();
                int currCol;
                source >> currCol;
                getline(source, line, ':');
                source.get();
                int strength;
                source >> strength;
                getline(source, line, ':');
                source.get();
                int stamina;
                source >> stamina;
                getline(source, line, ':');
                source.get();
                int hitpoints;
                source >> hitpoints;
                newLevel->placePlayer(character,currRow,currCol,strength,stamina,hitpoints);
            }
            else if(playerTexture == "Zombie"){
                getline(source, line, ':');
                source.get();
                int currRow;
                source >> currRow;
                getline(source, line, ':');
                source.get();
                int currCol;
                source >> currCol;
                getline(source, line, ':');
                source.get();
                int strength;
                source >> strength;
                getline(source, line, ':');
                source.get();
                int stamina;
                source >> stamina;
                getline(source, line, ':');
                source.get();
                int hitpoints;
                source >> hitpoints;
                newLevel->placeZombie(currRow,currCol,strength,stamina);
            }

            else if(playerTexture == "ZombieAttack"){
                getline(source, line, ':');
                source.get();
                int currRow;
                source >> currRow;
                getline(source, line, ':');
                source.get();
                int currCol;
                source >> currCol;
                getline(source, line, ':');
                source.get();
                int strength;
                source >> strength;
                getline(source, line, ':');
                source.get();
                int stamina;
                source >> stamina;
                getline(source, line, ':');
                source.get();
                int hitpoints;
                source >> hitpoints;
                newLevel->placeZombieAttack(currRow,currCol,strength,stamina);
            }
            else if(playerTexture == "ZombieGuard"){
                getline(source, line, ':');
                source.get();
                int currRow;
                source >> currRow;
                getline(source, line, ':');
                source.get();
                int currCol;
                source >> currCol;
                getline(source, line, ':');
                source.get();
                int strength;
                source >> strength;
                getline(source, line, ':');
                source.get();
                int stamina;
                source >> stamina;
                getline(source, line, ':');
                source.get();
                int hitpoints;
                source >> hitpoints;
                getline(source, line, ':');
                source.get();
                int lastmove;
                source >> lastmove;
                getline(source, line, ':');
                source.get();
                string muster;
                source >> muster;
                newLevel->placeZombieGuard(currRow,currCol,strength,stamina,lastmove,muster);
            }
        }
        getline(source, line);
        getline(source, line);
        getline(source, line, ':');
        source.get();
        int numberConnections;
        source >> numberConnections;
        for(int i = 0; i< numberConnections; i++){
            getline(source, line, ' ');
            getline(source, line);
            string connectionName(line);
            if(connectionName == "Portal"){
                getline(source, line, ':');
                source.get();
                int row;
                source >> row;
                getline(source, line, ':');
                source.get();
                int col;
                source >> col;
                getline(source, line, ':');
                source.get();
                int LinkRow;
                source >> LinkRow;
                getline(source, line, ':');
                source.get();
                int LinkCol;
                source >> LinkCol;
                newLevel->Link2Portal(row,col,LinkRow,LinkCol);
                getline(source, line);
            }
            else if(connectionName == "Switch"){
                getline(source, line, ':');
                source.get();
                int switchrow;
                source >> switchrow;
                getline(source, line, ':');
                source.get();
                int switchcol;
                source >> switchcol;
                getline(source, line, ':');
                source.get();
                int DoorRow;
                source >> DoorRow;
                getline(source, line, ':');
                source.get();
                int DoorCol;
                source >> DoorCol;
                newLevel->attachDoorToSwitch(switchrow,switchcol,DoorRow,DoorCol);
                getline(source, line);
            }
            else if(connectionName == "Levelchanger"){
                getline(source, line);
                getline(source, line);
                getline(source, line);
                getline(source, line);
                getline(source, line);
            }
        }
        level_list.push_back(newLevel);
    }
    //connectLevel();
    source.close();
    return true;
}

void DungeonCrawler::WriteFile(std::string path)
{
    ofstream target(path, std::ofstream::trunc);

    if(!target.good()){
        std::cerr << path << " kann nicht geÃ¶ffnet werden!\n";
        return;
    }

    target << "=================================LEVEL_LIST" << endl;
    target << "Number_Level: " << getLevelListSize() << endl;
    List::iterator iterator = level_list.begin();
    while(iterator != level_list.end()){
        auto lvl=*iterator;
        target << "=================================" << endl;
        target << "*********** " << lvl->getName() << ":\n";// << endl;
        target << "Breite: " << lvl->getBreite() << endl;
        target << "Hohe: " << lvl->getHohe() << endl;
        target << "******" << "Tiles:" << endl;
        for(int i=1; i<= lvl->getBreite(); i++){
            for(int j=1; j<=lvl->getHohe();j++){
                auto tile = lvl->getTile(i,j);
                string A = tile->getTexture();
                target << "**** " << tile->getTexture() << "\n";// endl;
                target << "Row: " << tile->getRow() << endl;
                target << "Col: " << tile->getCol() << endl;
                if(typeid(*tile) == typeid(Portal)){
                    Portal* p = dynamic_cast<Portal*>(tile);
                    target << "TypePortal: " << p->getTypePortal() << endl;
                }
                if(typeid(*tile) == typeid(LevelChanger)){
                    LevelChanger* l = dynamic_cast<LevelChanger*>(tile);
                    target << "Type: " << l->getLevelChangerType() << endl;
                }
                if(typeid(*tile) == typeid(Door)){
                    Door* d = dynamic_cast<Door*>(tile);
                    target << "Status: " << d->getisOpend() << endl;
                }
            }
        }
        target << "********" << "Character:" << endl;
        auto characterlist = lvl->getCharacterlist();
        target << "Number_Character: " << characterlist.size() << endl;
        for(auto character : characterlist){
            target << "**** " << character->getTexture() << endl;
            target << "Row: " << character->getTile()->getRow() << endl;
            target << "Col: " << character->getTile()->getCol() << endl;
            target << "Strength: " << character->getStrength() << endl;
            target << "Stamina: " << character->getStamina() << endl;
            target << "Hitpoints: " << character->getHitpoints() << endl;
            if(typeid(*character) == typeid(ZombieGuard)){
                GuardController* g = dynamic_cast<GuardController*>(character->getController());
                target << "lastMove: " << g->getLastMove() << endl;
                target << "MovePattern: " << g->getMuster() << endl;
            }
        }
        target << "******" << "Connection:" << endl;
        target <<"Number_Connections: "<< countConnections(lvl) << endl;
        for(int i=1; i<= lvl->getBreite(); i++){
            for(int j=1; j<=lvl->getHohe();j++){
                auto tile = lvl->getTile(i,j);
                if(typeid(*tile) == typeid(Portal)){
                    target << "**** " << tile->getTexture() << endl;
                    Portal* p = dynamic_cast<Portal*>(tile);
                    target << "Row: " << p->getRow() << endl;
                    target << "Col: " << p->getCol() << endl;
                    target << "LinkPortalRow: " << p->getLinkPortal()->getRow() << endl;
                    target << "LinkPortalCol: " << p->getLinkPortal()->getCol() << endl;
                }
                else if(typeid(*tile) == typeid(Switch)){
                    target << "**** " << tile->getTexture() << endl;
                    Switch* s = dynamic_cast<Switch*>(tile);
                    target << "Row: " << s->getRow() << endl;
                    target << "Col: " << s->getCol() << endl;
                    for(auto obj : s->getPassiveObjects()){
                        Door* d = dynamic_cast<Door*>(obj);
                        target << "PassiveObjectRow: " << d->getRow() << endl;
                        target << "PassiveObjectCol: " << d->getCol() << endl;
                    }
                }
                else if(typeid(*tile) == typeid(LevelChanger)){
                    target << "**** " << tile->getTexture() << endl;
                    LevelChanger* l = dynamic_cast<LevelChanger*>(tile);
                    target << "Row: " << l->getRow() << endl;
                    target << "Col: " << l->getCol() << endl;
                    target << "Level: " << l->getLevel()->getName() << endl;
                    target << "LinkLevelChangerRow: " << l->getLinkLevelChanger()->getRow() << endl;
                    target << "LinkLevelChangerCol: " << l->getLinkLevelChanger()->getCol() << endl;
                }
            }
        }
        if(iterator.getNextLevel() == nullptr){
            break;
        }
        ++iterator;
    }
    target.close();
}

bool DungeonCrawler::LoadSaveFile(std::string path, Player *character)
{
    while(level_list.size() != 0){
        level_list.pop_back();
    }

    if(!ReadFile(path,character)){
        return false;
    }
    for(List::iterator iter = level_list.begin(); iter != level_list.end(); ++iter){
        auto lvl = *iter;
        if(lvl->checkCharacterinLevel()){
            iterator = iter;
            level = *iterator;
            isChangedLevel=true;
            return true;
        }
    }
    return false;
}

int DungeonCrawler::countConnections(Level *lvl)
{
    int count = 0;
    for(int i=1; i<= lvl->getBreite(); i++){
        for(int j=1; j<=lvl->getHohe();j++){
            auto tile = lvl->getTile(i,j);
            if(typeid(*tile) == typeid(Portal)){
                count++;
            }
            else if(typeid(*tile) == typeid(Switch)){
                count++;
            }
            else if(typeid(*tile) == typeid(LevelChanger)){
                count++;
            }
        }
    }
    return count;
}

size_t DungeonCrawler::getLevelListSize()
{
    List::iterator iter = level_list.begin();
    int num = 0;
    while(iter != level_list.end()){
        num++;
        if(iter.getNextLevel()==nullptr){
            break;
        }
        ++iter;
    }
    return num;
}
