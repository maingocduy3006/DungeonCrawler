#include "tile.h"

Tile::Tile(string texture, int row, int col): Texture(texture), character(nullptr), Row(row), Col(col)
{
}

int Tile::getRow()
{
    return Row;
}

int Tile::getCol()
{
    return Col;
}

Character *Tile::getCharacter()
{
    return character;
}

bool Tile::isRightTile(int row, int col)
{
    if ((Row == row)&&(Col == col)){
        return true;
    }
    return false;
}

bool Tile::hasCharacter()
{
    if (character == nullptr){
        return false;
    }
    return true;
}

bool Tile::moveTo(Tile *desTile, Character* who)
{
    Tile* fromTile = this->onLeave(desTile, who);
    Tile* realDesTile = desTile->onEnter(fromTile, who);
    if((fromTile != nullptr)&&(realDesTile != nullptr)){
        if(!realDesTile->hasCharacter()){
            fromTile->setCharacter(nullptr);
            realDesTile->setCharacter(who);
            who->setTile(realDesTile);
            return true;
        }
        else{
            if(realDesTile->getCharacter()->getIsHuman() == who->getIsHuman()){
                return true;
            }
            else{
                Fight(who, realDesTile->getCharacter());
                if(who->getisAlive()){
                    fromTile->setCharacter(nullptr);
                    realDesTile->setCharacter(who);
                    who->setTile(realDesTile);
                    return true;
                }
                else{
                    return true;
                }
            }
        }
    }
    return false;
}
void Tile::setCharacter(Character *c){
    character = c;
}

Tile* Tile::onLeave(Tile *desTile, Character *who)
{
    return this;
}

Tile *Tile::CheckOnLeave(Tile *desTile)
{
    return this;
}

void Tile::Fight(Character *attacker, Character *defender)
{
    bool takeTurn = true; // true = attackerturn , false = defenderturn
    while(attacker->getisAlive()&&defender->getisAlive()){
        if(takeTurn){
            attacker->attack(defender);
        }
        else{
            defender->attack(attacker);
        }
        takeTurn=!takeTurn;
    }
    if(!attacker->getisAlive()){
        attacker->getTile()->setCharacter(nullptr);
        attacker->setTile(nullptr);
    }
    if(!defender->getisAlive()){
        defender->getTile()->setCharacter(nullptr);
        defender->setTile(nullptr);
    }
}

bool Tile::operator==(const Tile *other) const
{
    if(Row == other->Row){
        return Col == other->Col;
    }
    return Row == other->Row;
}
