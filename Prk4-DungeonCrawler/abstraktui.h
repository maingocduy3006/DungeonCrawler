#ifndef AbstraktUI_h
#define AbstraktUI_h

#include <stdio.h>
#include "level.h"

class AbstraktUI
{
public:
    AbstraktUI();
    virtual void draw(Level* level) = 0;
};

#endif
