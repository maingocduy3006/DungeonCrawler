#include <iostream>
#include "character.h"
#include "tile.h"

using std::cout;
using std::cin;

Character::Character(string texture, Controller* controller, int strength, int stamina, bool ishuman):
    Texture(texture),
    tile(nullptr),
    controller(controller),
    Strength(strength),
    Stamina(stamina),
    Hitpoints(getMaxHP()),
    isHuman(ishuman),
    isAlive(true)
{
}

Character::~Character()
{
    delete tile;
    delete controller;
}

string Character::getTexture() const
{
    return Texture;
}

Tile* Character::getTile() const
{
    return tile;
}

Controller* Character::getController() const
{
    return controller;
}

char Character::getMoveDirection() const
{
    return moveDirextion;
}

char Character::move(Level *level)
{
    moveDirextion = controller->move();
    return moveDirextion;
}

int Character::getMaxHP() const
{
    return 20+Stamina*5;
}

bool Character::getIsHuman() const
{
    return isHuman;
}

bool Character::getisAlive() const
{
    return isAlive;
}

int Character::getStrength() const
{
    return Strength;
}

int Character::getStamina() const
{
    return Stamina;
}

int Character::getHitpoints() const
{
    return Hitpoints;
}

void Character::isHit(int damage)
{
    Hitpoints = Hitpoints - damage;
    isAlive = Hitpoints > 0;
}

void Character::attack(Character *defender)
{
    defender->isHit(Strength);
}

void Character::setTile(Tile *newTile)
{
    tile = newTile;
}

void Character::setController(Controller *con)
{
    controller = con;
}

void Character::setStrength(int newStrength)
{
    Strength = newStrength;
}

void Character::setStamina(int newStamina)
{
    Stamina = newStamina;
}

void Character::setHitpoints(int newHitpoints)
{
    Hitpoints = newHitpoints;
}
