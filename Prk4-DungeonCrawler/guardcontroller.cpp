#include "guardcontroller.h"
#include <iostream>

GuardController::GuardController(std::string muster):Controller(), Muster(muster), lastMove(0)
{
}

void GuardController::incrementMove()
{
    lastMove++;
}

char GuardController::move()
{
    if(lastMove == Muster.size()){
        lastMove = 0;
    }
    auto i = lastMove;
    lastMove++;
    std::cout << Muster[i] << std::endl;;
    return Muster[i];
}

const std::string &GuardController::getMuster() const
{
    return Muster;
}

size_t GuardController::getLastMove() const
{
    return lastMove;
}

void GuardController::setLastMove(size_t newLastMove)
{
    lastMove = newLastMove;
}

