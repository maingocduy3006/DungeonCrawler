#ifndef Controller_h
#define Controller_h

class Controller
{
public:
    Controller();
    virtual ~Controller() = default;
    virtual char move() = 0;
};

#endif /* Controller_hpp */
