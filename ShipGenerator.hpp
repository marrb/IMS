#ifndef SHIP_GENERATOR
#define SHIP_GENERATOR

#include <simlib.h>

class ShipGenerator : public Process {
    public:
        ShipGenerator(int DayShipAvg);

        ~ShipGenerator() override;

        void Behavior() override;

    private:
        int DayShipAvg;
};

#endif