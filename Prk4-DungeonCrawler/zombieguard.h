#ifndef ZOMBIEGUARD_H
#define ZOMBIEGUARD_H

#include "character.h"
#include "guardcontroller.h"

class ZombieGuard: public Character
{
public:
    ZombieGuard(int, int, string musterMove);
    ~ZombieGuard() override;
    char move(Level *level) override;
    string getTexture() const override;
    void setLastMove(size_t lastMove);
private:
    GuardController* grdcontroller;
};

#endif // ZOMBIEGUARD_H
