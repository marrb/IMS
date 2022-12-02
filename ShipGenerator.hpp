#ifndef SHIP_GENERATOR
#define SHIP_GENERATOR

#include <simlib.h>

class ShipGenerator : public Process {
    public:
        ShipGenerator(int DayShipAvg);

        void Behavior() override;

    private:
        int DayShipAvg;
};

#endif