#include "ShipGenerator.hpp"
#include "Ship.hpp"
#include <iostream>

using namespace std;

ShipGenerator::ShipGenerator(int DayShipAvg){
    DayShipAvg = DayShipAvg;
}

ShipGenerator::~ShipGenerator(){

}

void ShipGenerator::Behavior(){
    (new Ship)->Activate();
    cout << "Serus";
    Activate(Time + Exponential(1));
}