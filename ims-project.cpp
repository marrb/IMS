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

int main(int argc, char **argv){
    int option;
    static const struct option longOptions[] = {
        {}
    };

    while((option = getopt_long(argc, argv, "", longOptions, nullptr)) != -1){
        switch (option){
            case 'f':
                break;

            case 'h':
            default:
                printHelp();
                exit(0);
        }
    }


    return 0;
}