#include "zombie.h"

Zombie::Zombie(int strength, int stamina):
    Character("Zombie", (staController = new StationaryController()),strength,stamina,false)
{
}

Zombie::~Zombie()
{
    delete staController;
}

string Zombie::getTexture() const
{
    return "Zombie";
}

char Zombie::move(Level *level)
{
    return moveDirextion = staController->move();
}
