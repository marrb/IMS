//
// Created by adase on 2. 12. 2022.
//
#include "Timeout.h"
#include "Ship.hpp"
#include <stdio.h>
#include <random>
#include <ctime>
Ship::Ship(Facility *docks){
    Ship::docks = docks;
    is_starting = Random() <= 0.05;

    if(is_starting){
        capacity_load = Exponential(15000);
    }
    else{
        capacity_unload = Exponential(7000);
        capacity_load = Exponential(capacity_unload/1.2);
    }
}

void Ship::Behavior(){
    Timeout_docks *tm = new Timeout_docks(this);
    tm->Activate(Uniform(4320, 10080));//čas s minútach
    Seize(*docks);
    if((docks)->In() && is_starting){
        Print("Isla do kokota\n");
        return;
    }
    Release(*docks);


}

void Ship::Timeout() {
    Out();
    Activate();
}