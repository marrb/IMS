#include "ShipGenerator.hpp"
#include "Ship.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

ShipGenerator::ShipGenerator(unsigned int docks, unsigned int cranes, unsigned int DayShipAvg){
    ShipGenerator::DayShipAvg = DayShipAvg; //Average number of ships that come to the port each day
    ShipGenerator::docks = docks;           //Number of docks in the port   
    ShipGenerator::cranes = cranes;         //Number of cranes per dock
    ShipGenerator::ship_dock_wait = new Stat("Ship waiting for dock duration");
    //Initialize dock facilities
    dock_facilities = new Facility*[docks];

    for(unsigned int i = 0; i < docks; i++){
        dock_facilities[i] = new Facility;
    }
}

void ShipGenerator::Behavior(){
    //Ship generation
    (new Ship(dock_facilities,
              &ship_Q,
              docks,
              cranes,
              ship_dock_wait/*,
              ship_leave_without_dock,
              ship_leave_while_loading,
              loaded_containers_per_day,
              unloaded_containers_per_day,
              avarege_ship_invoke_time,
              free_dock_capacity*/
              ))->Activate();
    Activate(Time + Exponential(1440.0 / DayShipAvg));
}