//
// Created by adase on 2. 12. 2022.
//
#include <stdbool.h>

#ifndef IMS_SHIP_H
#define IMS_SHIP_H

#include <simlib.h>


class Ship : public Process {
    public:
        Ship(Facility **docks, Queue *ship_Q, unsigned int dock_count);

        void Behavior() override;
        void Timeout();
private:
        bool is_starting;
        int capacity_load;
        int capacity_unload;
        unsigned int dock_count;
        Facility **docks;
        Queue *ship_Q;


        const int AVARAGE_AVAILABLE_TIME_IN_PORT = 5;
};


#endif
