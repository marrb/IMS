//
// Created by adase on 2. 12. 2022.
//

#ifndef IMS_TIMEOUT_H
#define IMS_TIMEOUT_H
#include "Ship.hpp"

class Timeout_ship : public Event {
    public:
        Timeout_ship(Ship *to) : Event(), To(to){
        };

        void Behavior();

        Ship *To;
};


#endif //IMS_TIMEOUT_H
