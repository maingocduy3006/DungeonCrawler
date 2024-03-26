#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H
#include "controller.h"
#include <string>

class GuardController: public Controller
{
private:
    std::string Muster;
    size_t lastMove;
public:
    GuardController(std::string muster);
    ~GuardController() override = default;
    void incrementMove();
    char move() override;
    const std::string &getMuster() const;
    size_t getLastMove() const;
    void setLastMove(size_t newLastMove);
};

#endif // GUARDCONTROLLER_H
