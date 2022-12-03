//
// Created by adase on 2. 12. 2022.
//
#include <stdbool.h>

#ifndef IMS_SHIP_H
#define IMS_SHIP_H

#include <simlib.h>


class Ship : public Process {
        public:
                Ship(Facility **docks,
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
                     );

                void Behavior() override;
                void Timeout();

                /**
                 * @brief Ship loading process
                 * 
                 */
                void Loading();

                /**
                 * @brief Ship unloading process
                 * 
                 */
                void Unloading();

        private:
                bool is_starting;               //Indicates if the ship's starting location is this port (ship is empty)
                int capacity_load;              //Containers to load on to the ship
                int capacity_unload;            //Containers to unload from the ship
                unsigned int dock_count;        //Number of ocks in the port
                Facility **docks;               //Dock facilities
                Queue *ship_Q;                  //Ship queue
                int fac_idx = -1;               //Facility index that the ship seized
                bool timeout_occured = false;   //Flag if timeout occured
                unsigned int cranes;            //Number of cranes per dock
                bool isLoading = false;         //Indicates if the ship is currently loading

                Stat *ship_dock_wait;
                double dock_wait_time = 0;

                unsigned int *ship_leave_without_dock;
                unsigned int *ship_leave_while_loading;
                unsigned int *loaded_containers_per_day;
                unsigned int *unloaded_containers_per_day;

                Stat *average_ship_in_dock_time;
                double in_dock_time = 0;

                Stat *free_dock_capacity;
                unsigned int free_docks = 0;
};


#endif
