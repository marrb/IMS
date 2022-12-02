//
// Created by adase on 2. 12. 2022.
//
#include <stdbool.h>

#ifndef IMS_SHIP_H
#define IMS_SHIP_H

#include <simlib.h>


class Ship : public Process {
    public:
        Ship(Facility *docks);

        void Behavior() override;
        void Timeout();
private:
        bool is_starting;
        int capacity_load;
        int capacity_unload;
        Facility *docks;


        const int AVARAGE_AVAILABLE_TIME_IN_PORT = 5;
};


#endif
