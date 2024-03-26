#include "door.h"

Door::Door(int row, int col):Tile("Door", row, col), Floor(row, col), Wall(row, col), Passive(), isOpen(false), mustReInitGraph(true)
{
}

Door::Door(int row, int col, bool isopen):Tile("Door", row, col), Floor(row, col), Wall(row, col), Passive(), isOpen(isopen), mustReInitGraph(true)
{
}

bool Door::getisOpend()
{
    return isOpen;
}

string Door::getTexture()
{
    if (isOpen)
        return "OpenDoor";
    else
        return "CloseDoor";
}

bool Door::getMustReInitGraph() const
{
    return mustReInitGraph;
}

void Door::setMustReInitGraph(bool newMustReInitGraph)
{
    mustReInitGraph = newMustReInitGraph;
}

Tile *Door::CheckOnEnter(Tile *fromTile)
{
    if(isOpen){
        return Floor::CheckOnEnter(fromTile);
    }
    else{
        return Wall::CheckOnEnter(fromTile);
    }
}

Tile *Door::CheckOnLeave(Tile *desTile)
{
    if(isOpen){
        return Floor::CheckOnLeave(desTile);
    }
    else{
        return Wall::CheckOnLeave(desTile);
    }
}

void Door::notify(Active* source)
{
    isOpen = !isOpen;
    mustReInitGraph = true;
}

Tile* Door::onEnter(Tile* fromTile, Character* who)
{
    if(isOpen){
        return Floor::onEnter(fromTile, who);
    }
    else{
        return Wall::onEnter(fromTile, who);
    }
}

Tile *Door::onLeave(Tile *desTile, Character *who)
{
    if(isOpen){
        return Floor::onLeave(desTile, who);
    }
    else{
        return Wall::onLeave(desTile, who);
    }
}

