#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include "controller.h"

class AttackController: public Controller
{
private:
    char nextMove;
public:
    AttackController();
    ~AttackController() override = default;
    char move() override;
    void setNextMove(char newNextMove);
};

#endif // ATTACKCONTROLLER_H
