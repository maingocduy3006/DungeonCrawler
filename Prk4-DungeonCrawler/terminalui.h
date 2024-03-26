#ifndef Terminal_h
#define Terminal_h

#include "abstraktui.h"
#include "controller.h"

class TerminalUI: public AbstraktUI, public Controller
{
public:
    TerminalUI();
    void draw(Level* level) override;
    Level* setUpSpielfeld();
    char move() override;
};

#endif /* Terminal_h */
