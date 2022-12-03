//
// Created by adase on 2. 12. 2022.
//

#include "Timeout.h"
void Timeout_ship::Behavior(){
    //Call timeout method and cancel this
    To->Timeout();
    Cancel();
}