#include <getopt.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <simlib.h>

using namespace std;

#define DEFAULT_NUMBER_OD_DOCKS 5
#define DEFAULT_NUMBER_OF_SHIPS 10
#define DEFAULT_NUMBER_OF_SIM_DAYS 1
#define DEFAULT_NUMBER_OF_CRANES 1

void printHelp(){
    puts("usage: [sudo] ./ims-project [-d <number of cargo docks>] [-s <number of ships per day>] [-D <days of simulation>] [-c <cargo cranes per dock>] [-h]\n");
    puts("-d <number of cargo docks> : defines the number of avalaible cargo docks in your port (default: 5)");
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
                    printf("Invalid argument in option 'd'!");
                    exit(1);
                }
                break;

            case 's':
                if((my_args.ships = atoi(optarg)) <= 0){
                    printf("Invalid argument in option 's'!");
                    exit(1);
                }
                break;
            
            case 'D':
                if((my_args.days = atoi(optarg)) <= 0){
                    printf("Invalid argument in option 'D'!");
                    exit(1);
                }
                break;

            case 'c':
                if((my_args.cranes = atoi(optarg)) <= 0){
                    printf("Invalid argument in option 'c'!");
                    exit(1);
                }
                break;

            case 'h':
                break;
            default:
                printHelp();
                exit(0);
        }
    }


    return 0;
}