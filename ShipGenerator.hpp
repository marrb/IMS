#ifndef SHIP_GENERATOR
#define SHIP_GENERATOR

#include <simlib.h>

class ShipGenerator : public Event {
    public:
        ShipGenerator(unsigned int docks, unsigned int cranes, unsigned int DayShipAvg, Stat *ship_dock_wait);

        void Behavior() override;

    private:
        unsigned int DayShipAvg;    //Average number of ships that come to the port per day
        unsigned int docks;         //Number of cargo docks in the port
        unsigned int cranes;        //Number of container cranes per dock
        Facility **dock_facilities; //Dock facilities
        Queue ship_Q;               //Ship queue

        Stat *ship_dock_wait;       //Time before ship got dock
/*        Stat *ship_leave_without_dock;
        Stat *ship_leave_while_loading;
        Stat *loaded_containers_per_day;
        Stat *unloaded_containers_per_day;
        Stat *avarege_ship_invoke_time;
        Stat *free_dock_capacity;*/





};

#endif
