#include "ShipGenerator.hpp"
#include "Ship.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

ShipGenerator::ShipGenerator(unsigned int docks, unsigned int cranes, unsigned int DayShipAvg){
    ShipGenerator::DayShipAvg = DayShipAvg; //Average number of ships that come to the port each day
    ShipGenerator::docks = docks;           //Number of docks in the port   
    ShipGenerator::cranes = cranes;         //Number of cranes per dock

    //Initialize dock facilities
    dock_facilities = new Facility*[docks];

    for(unsigned int i = 0; i < docks; i++){
        dock_facilities[i] = new Facility;
    }
}

void ShipGenerator::Behavior(){
    //Ship generation
    (new Ship(dock_facilities, &ship_Q, docks, cranes))->Activate();
    Activate(Time + Exponential(1440.0 / DayShipAvg));
}