#ifndef SHIP_GENERATOR
#define SHIP_GENERATOR

#include <simlib.h>

class ShipGenerator : public Event {
    public:
        ShipGenerator(unsigned int docks,
                      unsigned int cranes, 
                      unsigned int DayShipAvg,
                      Stat *ship_dock_wait,
                      unsigned int *ship_leave_without_dock,
                      unsigned int *ship_leave_while_loading,
                      unsigned int *loaded_containers_per_day,
                      unsigned int *unloaded_containers_per_day,
                      Stat *average_ship_in_dock_time,
                      Stat *free_dock_capacity
                    );

        void Behavior() override;

    private:
        unsigned int DayShipAvg;    //Average number of ships that come to the port per day
        unsigned int docks;         //Number of cargo docks in the port
        unsigned int cranes;        //Number of container cranes per dock
        Facility **dock_facilities; //Dock facilities
        Queue ship_Q;               //Ship queue



        Stat *ship_dock_wait;                       //Time before ship got dock
        unsigned int *ship_leave_without_dock;      //Number of ships that left without getting dock
        unsigned int *ship_leave_while_loading;     //Number of ships that had to left while being loaded
        unsigned int *loaded_containers_per_day;    //Number of loaded containers per the length of simulation
        unsigned int *unloaded_containers_per_day;  //Number of unloaded containers per length of simulation
        Stat *average_ship_in_dock_time;            //Time that ships spent in the dock
        Stat *free_dock_capacity;                   //Number of free docks at one time





};

#endif
