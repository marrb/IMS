#include "ShipGenerator.hpp"
#include "Ship.h"

ShipGenerator::ShipGenerator(int DayShipAvg){
    ShipGenerator::DayShipAvg = DayShipAvg;
}

void ShipGenerator::Behavior(){
    (new Ship)->Activate();
    Activate(Time + Exponential(24.0 / DayShipAvg));
}