#include "ShipGenerator.hpp"
#include "Ship.hpp"
#include <iostream>
#include <cstdlib>
#include <iostream>
const int POC = 5;
using namespace std;

ShipGenerator::ShipGenerator(unsigned int docks, unsigned int cranes, unsigned int DayShipAvg){
    ShipGenerator::DayShipAvg = DayShipAvg;
    ShipGenerator::docks = docks;
    ShipGenerator::cranes = cranes;
    //ShipGenerator::dock_facilities = (Facility*) malloc(docks * sizeof(Facility));

}

void ShipGenerator::Behavior(){
    (new Ship(dock_facilities))->Activate();
    Activate(Time + Exponential(1440.0 / DayShipAvg));
}