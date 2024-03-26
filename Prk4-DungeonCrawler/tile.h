#ifndef Tile_h
#define Tile_h

#include <stdio.h>
#include <string>
#include "character.h"

using std::string;

class Tile
{
public:
    Tile(string texture, int row, int col);
    virtual ~Tile() = default;
    virtual string getTexture() = 0;
    int getRow();
    int getCol();
    Character* getCharacter();

    bool isRightTile(int row, int col);
    bool hasCharacter();
    void setCharacter(Character* c);

    bool moveTo(Tile* desTile, Character* who);
    virtual Tile* onEnter(Tile* fromTile, Character* who) = 0;
    virtual Tile* onLeave(Tile* desTile, Character* who);

    virtual Tile* CheckOnEnter(Tile* fromTile) = 0;
    virtual Tile* CheckOnLeave(Tile* desTile);

    void Fight(Character *attacker, Character *defender);

    bool operator==(const Tile* other) const;
protected:
    string Texture;
    Character* character;
    const int Row;
    const int Col;
};


#endif /* Tile_h */
