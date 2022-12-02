//
// Created by adase on 2. 12. 2022.
//

#ifndef IMS_SHIP_H
#define IMS_SHIP_H


class Ship : public Process {
public:
    Ship();
    
    int Capacity;

    const int AVARAGE_AVAILABLE_TIME_IN_PORT = 5;

    void Behavior() override;
};


#endif
