#ifndef Passive_h
#define Passive_h

#include "active.h"

class Passive{
public:
    Passive();
    virtual void notify(Active* source) = 0;
};

#endif
