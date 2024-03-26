#ifndef Active_h
#define Active_h

#include <vector>

using std::vector;

class Passive;

class Active{
protected:
    vector<Passive*> passivListe;
public:
    Active();
    bool checkPasList(Passive* pasObj);
    void attach(Passive* pasObj);
    void detach(Passive* pasObj);
    void activate();
};

#endif
