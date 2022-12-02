#include <iostream>
#include <getopt.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "simlib.h"
#include "ShipGenerator.hpp"

#define SIMULATION_START_TIME 0.0
#define SIMULATION_END_TIME 24.0 * 60.0

#define DEFAULT_NUMBER_OD_DOCKS 3
#define DEFAULT_NUMBER_OF_SHIPS 10
#define DEFAULT_NUMBER_OF_SIM_DAYS 1
#define DEFAULT_NUMBER_OF_CRANES 1

using namespace std;

void printHelp(){
    puts("usage: [sudo] ./ims-project [-d <number of cargo docks>] [-s <number of ships per day>] [-D <days of simulation>] [-c <cargo cranes per dock>] [-h]\n");
    puts("-d <number of cargo docks> : defines the number of avalaible cargo docks in your port (default: 3)");
    puts("-s <number of ships per day> : defines the average number of ships that come to the port troughout one day (default: 10)");
    puts("-D <days of simulation> : defines the number of days the simulation will run (default: 1)");
    puts("-c <cargo cranes per dock> : defines the number of cranes per cargo dock (default: 1)");
    puts("-h : prints help");
}

typedef struct {
    int cargo_docks;
    int ships;
    int days;
    int cranes;
} my_args;

int main(int argc, char **argv){
    int option;
    my_args my_args = {
        DEFAULT_NUMBER_OD_DOCKS,
        DEFAULT_NUMBER_OF_SHIPS,
        DEFAULT_NUMBER_OF_SIM_DAYS,
        DEFAULT_NUMBER_OF_CRANES
    };

    while((option = getopt_long(argc, argv, "d:s:D:c:h", nullptr, nullptr)) != -1){
        switch (option){
            case 'd':
                if((my_args.cargo_docks = atoi(optarg)) <= 0){
                    fprintf(stderr, "Invalid argument in option 'd'!");
                    exit(EXIT_FAILURE);
                }
                break;

            case 's':
                if((my_args.ships = atoi(optarg)) <= 0){
                    fprintf(stderr, "Invalid argument in option 's'!");
                    exit(EXIT_FAILURE);
                }
                break;
            
            case 'D':
                if((my_args.days = atoi(optarg)) <= 0){
                    fprintf(stderr, "Invalid argument in option 'D'!");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'c':
                if((my_args.cranes = atoi(optarg)) <= 0){
                    fprintf(stderr, "Invalid argument in option 'c'!");
                    exit(EXIT_FAILURE);
                }
                break;

            case 'h':
            default:
                printHelp();
                exit(EXIT_SUCCESS);
        }
    }

    Init(SIMULATION_START_TIME, SIMULATION_END_TIME);
    (new ShipGenerator(my_args.ships))->Activate();
    Run();
    SIMLIB_statistics.Output();


    return EXIT_SUCCESS;
}