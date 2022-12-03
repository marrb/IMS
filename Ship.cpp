//
// Created by adase on 2. 12. 2022.
//
#include "Timeout.h"
#include "Ship.hpp"
#include <stdio.h>
#include <ctime>

Ship::Ship(Facility **docks,
           Queue *ship_Q,
           unsigned int dock_count,
           unsigned int cranes,
           Stat *ship_dock_wait
           ){
    Ship::docks = docks;            //Dock facilities
    is_starting = Random() <= 0.05; //With 5% probability this port is the ship's first destination (ship is empty)
    Ship::ship_Q = ship_Q;          //Ship queue
    Ship::dock_count = dock_count;  //Number of cargo docks in port
    Ship::cranes = cranes;          //Number of cranes per cargo dock
    Ship::ship_dock_wait = ship_dock_wait; // stats: Ship waiting for dock duration

    if(is_starting){
        //If the ship is starting at this port, it has to load more containers
        capacity_load = Exponential(15000);
    }
    else{
        //Else if the ship is coming from different port it will unload less containers but also load some
        capacity_unload = Exponential(7000);
        capacity_load = Exponential(capacity_unload/1.2);
    }
}

void Ship::Behavior(){
    //Start timeout 
    Timeout_ship *tm = new Timeout_ship(this);
    //Ships wait in the port from 3 - 7 days
    tm->Activate(Time + Uniform(4320, 10080));

    while(1){
        //Check if there is an empty dock
        for(unsigned int i = 0; i < dock_count; i++){
            if(!docks[i]->Busy()){
                fac_idx = (int) i;
                break;
            }
        }
        //If an empty dock is found continue
        if(fac_idx != -1) break;
        else{
            //Else wait in the queue until there is dock avalaible
            Into(ship_Q);
            Passivate();
        }
    }
    //Seize avalaible dock
    Seize(*docks[fac_idx]);
    
    //Wait until the ship parks
    Wait(Exponential(15.0));

    //If the ship is starting at this port, just load containers (ship is empty)
    if(is_starting) Ship::Loading();
    else{
        //Else Unload containers
        Ship::Unloading();

        //If timeout occured while the ship was unloading, leave
        if(timeout_occured){
            Release(*docks[fac_idx]);
            Cancel();
        }

        //Else with 90% probability load containers else leave
        if(Random() <= 0.90) Ship::Loading();
    }

    //Release dock
    Release(*docks[fac_idx]);
    tm->Cancel();
    //Activate waiting ship
    if(ship_Q->Length() > 0) ship_Q->GetFirst()->Activate();
}

void Ship::Timeout() {
    //If the ship is starting in this port and timeout occurs, leave
    if(is_starting) Cancel();
    timeout_occured = true;
}

void Ship::Loading(){
    for(int i = 0; i < capacity_load ; i++){
     Wait(0.36 / cranes);
     if(timeout_occured){
        Release(*docks[fac_idx]);
        Cancel();
     }
    }
}

void Ship::Unloading(){
    Wait(capacity_unload * (0.36 / cranes));
}
