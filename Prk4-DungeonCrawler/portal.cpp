#include <stdio.h>
#include "portal.h"

Portal::Portal(int row, int col): Tile("Portal", row, col), LinkPortal(nullptr)
{
}

string Portal::getTexture()
{
    return "Portal";
}

Portal* Portal::getLinkPortal() const
{
    return LinkPortal;
}

int Portal::getTypePortal() const
{
    return Portaltype;
}

void Portal::setLinkPortal(Portal *portal)
{
    LinkPortal = portal;
}

void Portal::setPortalType(int num)
{
    Portaltype = num;
}

Tile* Portal::onEnter(Tile *fromTile, Character *who){
    return LinkPortal;
}

Tile *Portal::CheckOnEnter(Tile *fromTile)
{
    return LinkPortal;
}


