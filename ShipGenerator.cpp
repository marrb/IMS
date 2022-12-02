#include "ShipGenerator.hpp"
#include "Ship.hpp"
#include <iostream>

using namespace std;

ShipGenerator::ShipGenerator(unsigned int docks, unsigned int cranes, unsigned int DayShipAvg){
    ShipGenerator::DayShipAvg = DayShipAvg;
    ShipGenerator::docks = docks;
    ShipGenerator::cranes = cranes;
}

void ShipGenerator::Behavior(){
    //(new Ship)->Activate();
    cout << "AVG: " << DayShipAvg << "\n";
    Activate(Time + Exponential(1440.0 / DayShipAvg));
}