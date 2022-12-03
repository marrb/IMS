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
           Stat *ship_dock_wait,
           unsigned int *ship_leave_without_dock,
           unsigned int *ship_leave_while_loading,
           unsigned int *loaded_containers_per_day,
           unsigned int *unloaded_containers_per_day,
           Stat *average_ship_in_dock_time,
           Stat *free_dock_capacity
           ){
    Ship::docks = docks;            //Dock facilities
    is_starting = Random() <= 0.05; //With 5% probability this port is the ship's first destination (ship is empty)
    Ship::ship_Q = ship_Q;          //Ship queue
    Ship::dock_count = dock_count;  //Number of cargo docks in port
    Ship::cranes = cranes;          //Number of cranes per cargo dock

    Ship::ship_dock_wait = ship_dock_wait; // stats: Ship waiting for dock duration
    Ship::ship_leave_without_dock = ship_leave_without_dock;
    Ship::ship_leave_while_loading = ship_leave_while_loading;
    Ship::loaded_containers_per_day = loaded_containers_per_day;
    Ship::unloaded_containers_per_day = unloaded_containers_per_day;
    Ship::average_ship_in_dock_time = average_ship_in_dock_time;
    Ship::free_dock_capacity = free_dock_capacity;

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
                free_docks++;
            }
        }

        (*free_dock_capacity)(free_docks);
        //If an empty dock is found continue
        if(fac_idx != -1) break;
        else{
            //Else wait in the queue until there is dock avalaible
            Into(ship_Q);
            dock_wait_time = Time;
            Passivate();
        }
    }
    //Seize avalaible dock
    Seize(*docks[fac_idx]);
    if(dock_wait_time != 0) dock_wait_time = Time - dock_wait_time;
    (*ship_dock_wait)(dock_wait_time);

    in_dock_time = Time;

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
    (*average_ship_in_dock_time)(Time - in_dock_time);
}

void Ship::Timeout() {
    //If the ship is starting in this port and timeout occurs, leave
    if(is_starting){
        if(dock_wait_time != 0) dock_wait_time = Time - dock_wait_time;
        (*ship_dock_wait)(dock_wait_time);

        if(isLoading) *ship_leave_while_loading += 1;

        if(fac_idx != -1){
            Release(*docks[fac_idx]);
        }
        else{
            *ship_leave_without_dock += 1;
        }
        
        if(ship_Q->Length() > 0) ship_Q->GetFirst()->Activate();
        Cancel();
    }
    timeout_occured = true;
}

void Ship::Loading(){
    // Ship loading
    isLoading = true;

    for(int i = 0; i < capacity_load ; i++){
    // waiting to load one container
     Wait(0.18 / cranes);
     *loaded_containers_per_day += 1;
     // Ships must leave if the timeout occurs
     if(timeout_occured){
        Release(*docks[fac_idx]);
        if(ship_Q->Length() > 0) ship_Q->GetFirst()->Activate();
        Cancel();
     }
    }

    isLoading = false;
}

void Ship::Unloading(){
    // Ship unloading, ship can not leave
    Wait(capacity_unload * (0.18 / cranes));
    *unloaded_containers_per_day += capacity_unload;
}
