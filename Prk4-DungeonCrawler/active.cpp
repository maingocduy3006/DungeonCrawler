#include "active.h"
#include "passive.h"

Active::Active()
{
}

bool Active::checkPasList(Passive *pasObj)
{
    for(auto& p : passivListe){
        if (pasObj == p)
            return true;
    }
    return false;
}

void Active::attach(Passive *pasObj)
{
    if (!checkPasList(pasObj))
        passivListe.push_back(pasObj);
}

void Active::detach(Passive *pasObj)
{
    for(auto& p : passivListe){
        if (pasObj == p){
            std::swap(p, passivListe.back());
            passivListe.pop_back();
        }
    }
}

void Active::activate()
{
    for(auto& p : passivListe){
        p->notify(this);
    }
}


