PROJ=ims-project
CFLAGS= -std=c++17 -Wall -Wextra -Werror -pedantic
CC=g++
LIBS= -lsimlib
RM=rm -f
FILES=ims-project.cpp

$(PROJ) : $(FILES)
	$(CC) $(CFLAGS) -o $(PROJ) $(FILES) $(LIBS)
	
clean:
	$(RM) *.o $(PROJ)