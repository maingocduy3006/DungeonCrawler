#include "attackcontroller.h"

AttackController::AttackController(): Controller()
{
}

char AttackController::move()
{
    return nextMove;
}

void AttackController::setNextMove(char newNextMove)
{
    nextMove = newNextMove;
}
