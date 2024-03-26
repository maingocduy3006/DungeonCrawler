#ifndef Portal_h
#define Portal_h

#include "tile.h"

class Portal: public Tile
{
private:
    Portal* LinkPortal;
    int Portaltype;
public:
    Portal(int row, int col);
    string getTexture() override;
    Portal* getLinkPortal() const;
    int getTypePortal() const;

    void setLinkPortal(Portal* portal);
    void setPortalType(int num);
    Tile* onEnter(Tile* fromTile, Character* who) override;

    Tile* CheckOnEnter(Tile* fromTile) override;
};

#endif /* Portal_h */
