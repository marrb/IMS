//
// Created by adase on 2. 12. 2022.
//
#include "Timeout.h"
#include "Ship.hpp"
#include <stdio.h>
#include <random>
#include <ctime>
Ship::Ship(Facility *docks, Queue *ship_Q, unsigned int dock_count){
    Ship::docks = docks;
    is_starting = Random() <= 0.05;
    Ship::ship_Q = ship_Q;
    Ship::dock_count = dock_count;

    if(is_starting){
        capacity_load = Exponential(15000);
    }
    else{
        capacity_unload = Exponential(7000);
        capacity_load = Exponential(capacity_unload/1.2);
    }
}

void Ship::Behavior(){
    int fac_idx = -1;
    while(1){
        for(unsigned int i = 0; i < dock_count; i++){
            if(!docks[i].Busy()){
                fac_idx = (int) i;
                break;
            }
        }
        if(fac_idx != -1) break;
        else{
            Into(ship_Q);
            Passivate();
        }
    }
    Seize(docks[fac_idx]);
    Wait(1440);
    Release(docks[fac_idx]);
    if(ship_Q->Length() > 0) ship_Q->GetFirst()->Activate();
}

void Ship::Timeout() {
    Out();
    Activate();
}