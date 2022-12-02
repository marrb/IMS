#ifndef SHIP_GENERATOR
#define SHIP_GENERATOR

#include <simlib.h>

class ShipGenerator : public Event {
    public:
        ShipGenerator(unsigned int docks, unsigned int cranes, unsigned int DayShipAvg);

        void Behavior() override;

    private:
        unsigned int DayShipAvg;
        unsigned int docks;
        unsigned int cranes;
        Facility **dock_facilities;
        Queue ship_Q;
};

#endif