#include "player.h"

Player::Player(Controller* conTroller, int strength,  int stamina):
    Character("Player", conTroller, strength, stamina, true)
{
}

string Player::getTexture() const
{
    return "Player";
}

char Player::move(Level *level)
{
    return moveDirextion = controller->move();
}
