PROJ=ims-project
CFLAGS= -std=c++17 
CC=g++
LIBS= -lsimlib
RM=rm -f
FILES=ims-project.cpp ShipGenerator.cpp ShipGenerator.hpp Ship.cpp Timeout.cpp

$(PROJ) : $(FILES)
	$(CC) $(CFLAGS) -o $(PROJ) $(FILES) $(LIBS)
	
clean:
	$(RM) *.o $(PROJ)