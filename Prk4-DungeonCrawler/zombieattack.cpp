#include "zombieattack.h"
#include"tile.h"
#include"level.h"

ZombieAttack::ZombieAttack(int strength, int stamina):
    Character("ZombieAttack", (attackcontroller = new AttackController()), strength, stamina, false)
{
}

ZombieAttack::~ZombieAttack()
{
    delete attackcontroller;
}

char ZombieAttack::move(Level *level)
{
    auto path = level->getPath(tile);
    attackcontroller->setNextMove(path[0]);
    return moveDirextion = attackcontroller->move();
}

string ZombieAttack::getTexture() const
{
    return "ZombieAttack";
}

