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
    unsigned int cargo_docks;
    unsigned int ships;
    unsigned int days;
    unsigned int cranes;
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

    Stat *ship_dock_wait = new Stat("Ship waiting for dock duration");                      //Time before ship got dock
    unsigned int ship_leave_without_dock = 0;                                               //Number of ships that left without getting a dock
    unsigned int ship_leave_while_loading = 0;                                              //Number of ships that had to left while being loaded
    unsigned int loaded_containers_per_day = 0;                                             //Number of loaded containers per the length of simulation
    unsigned int unloaded_containers_per_day = 0;                                           //Number of unloaded containers per length of simulation
    Stat *average_ship_in_dock_time = new Stat("Time spent by ships being in the dock");    //Time that ships spent in the dock
    Stat *free_dock_capacity;

    cout << "-----------------------------------------------------------------------------\n"
        << "STARTING SIMULATION\n"
        << "Simulating with " << my_args.cargo_docks << " docks.\n"
        << "Simulating with average of " << my_args.ships << " ships per day.\n"
        << "Simulation will run for " << my_args.days << " days.\n"
        << "Simulating with " << my_args.cranes << " cranes per dock.\n"
        << "Simulation will run 5 times.\n"
        << "-----------------------------------------------------------------------------\n";

    for(int i = 1; i <= 5; i ++){
        cout << "-----------------------------------------------------------------------------\n"
            << "STARTING SIMULATION NUMBER " << i << "\n"
            << "-----------------------------------------------------------------------------\n";

        Init(SIMULATION_START_TIME, my_args.days * SIMULATION_END_TIME);
        (new ShipGenerator(my_args.cargo_docks,
                            my_args.cranes,
                            my_args.ships,
                            ship_dock_wait,
                            &ship_leave_without_dock,
                            &ship_leave_while_loading,
                            &loaded_containers_per_day,
                            &unloaded_containers_per_day,
                            average_ship_in_dock_time,
                            free_dock_capacity))->Activate();
        Run();
        SIMLIB_statistics.Output();


        //Statistics--------------------------------------------------------------------------------------------------------
        ship_dock_wait->Output();
        ship_dock_wait->Clear();

        cout << "Number of ships that left without getting a dock: " << ship_leave_without_dock << "\n";
        ship_leave_without_dock = 0;

        cout << "Number of ships that left while loading cargo: " << ship_leave_while_loading << "\n";
        ship_leave_while_loading = 0;
        
        cout << "Number of loaded containers per " << my_args.days << " days: " << loaded_containers_per_day << "\n";
        loaded_containers_per_day = 0;

        cout << "Number of unloaded containers per " << my_args.days << " days: " << unloaded_containers_per_day << "\n";
        unloaded_containers_per_day= 0;

        average_ship_in_dock_time->Output();
        average_ship_in_dock_time->Clear();
        //-----------------------------------------------------------------------------------------------------------------

        cout << "-----------------------------------------------------------------------------\n"
            << "SIMULATION NUMBER " << i << " ENDED \n"
            << "-----------------------------------------------------------------------------\n";
    }
    
    cout << "-----------------------------------------------------------------------------\n"
        << "SIMULATION ENDED\n"
        << "-----------------------------------------------------------------------------\n";

    return EXIT_SUCCESS;
}