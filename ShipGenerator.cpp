#include "ShipGenerator.hpp"
#include "Ship.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

ShipGenerator::ShipGenerator(unsigned int docks, unsigned int cranes, unsigned int DayShipAvg){
    ShipGenerator::DayShipAvg = DayShipAvg;
    ShipGenerator::docks = docks;
    ShipGenerator::cranes = cranes;

    dock_facilities = new Facility*[docks];

    for(unsigned int i = 0; i < docks; i++){
        dock_facilities[i] = new Facility;
    }
}

void ShipGenerator::Behavior(){
    (new Ship(*dock_facilities, &ship_Q, docks))->Activate();
    Activate(Time + Exponential(1440.0 / DayShipAvg));
}