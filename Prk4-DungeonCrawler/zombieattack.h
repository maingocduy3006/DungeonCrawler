#ifndef ZOMBIEATTACK_H
#define ZOMBIEATTACK_H

#include "character.h"
#include "attackcontroller.h"

class ZombieAttack: public Character
{
public:
    ZombieAttack(int, int);
    ~ZombieAttack() override;
    char move(Level *level) override;
    string getTexture() const override;

private:
    AttackController* attackcontroller;
};

#endif // ZOMBIEATTACK_H
