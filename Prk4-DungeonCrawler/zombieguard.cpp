#include "zombieguard.h"

ZombieGuard::ZombieGuard(int strength, int stamina, std::string musterMove):
    Character("ZombieGuard", (grdcontroller = new GuardController(musterMove)),strength,stamina,false)
{
}

ZombieGuard::~ZombieGuard()
{
    delete grdcontroller;
}

char ZombieGuard::move(Level *level)
{
    return moveDirextion = grdcontroller->move();
}

string ZombieGuard::getTexture() const
{
    return "ZombieGuard";
}

void ZombieGuard::setLastMove(size_t lastMove)
{
    grdcontroller->setLastMove(lastMove);
}
