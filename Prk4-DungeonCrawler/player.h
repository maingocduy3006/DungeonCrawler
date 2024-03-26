#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player: public Character
{
public:
    Player(Controller* controller,int,int);
    ~Player() override = default;
    string getTexture() const override ;
    char move(Level *level) override;
};

#endif // PLAYER_H
