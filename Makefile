
PROJ=ims-project
CFLAGS= -std=c++17 -Wall -Wextra -Werror -pedantic
CC=g++
LIBS= -lsimlib
RM=rm -f
FILES=ims-project.cpp ShipGenerator.cpp ShipGenerator.hpp Ship.cpp Timeout.cpp

$(PROJ) : $(FILES)
	$(CC) $(CFLAGS) -o $(PROJ) $(FILES) $(LIBS)
	
clean:
	$(RM) *.o $(PROJ)

run:
	./$(PROJ) -s 7 -d 7 -c 4 -D 365