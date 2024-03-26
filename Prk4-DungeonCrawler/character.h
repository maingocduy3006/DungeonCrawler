#ifndef Character_h
#define Character_h

#include "controller.h"
#include <string>

using std::string;

class Tile;
class Level;
class Character
{
protected:
    string Texture;
    char moveDirextion;
    bool isAlive;

    Tile* tile;
    Controller* controller;
    int Strength;
    int Stamina;
    int Hitpoints;
    bool isHuman;
public:
    Character(string texture, Controller* controller, int strength, int stamina, bool ishuman);
    virtual ~Character();
    virtual string getTexture() const;
    Tile* getTile() const;
    Controller* getController() const;
    char getMoveDirection() const;
    virtual char move(Level* level) = 0;
    int getMaxHP() const;
    bool getIsHuman() const;
    bool getisAlive() const;
    int getStrength() const;
    int getStamina() const;
    int getHitpoints() const;

    void isHit(int damage);
    void attack(Character *defender);

    void setTile(Tile* newTile);
    void setController(Controller* con);
    void setStrength(int newStrength);
    void setStamina(int newStamina);
    void setHitpoints(int newHitpoints);
};

#endif /* Character_h */
