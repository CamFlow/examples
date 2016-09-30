INCLUDES = -I/usr/local/include
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = /usr/local/lib/provenancelib.a -lpthread -lz

.SUFFIXES: .c

all: exec file fork pipe std tcp-client tcp-server

exec:
	$(CCC) $(INCLUDES) exec.c $(LIB) -o exec.o $(CCFLAGS)

file:
	$(CCC) $(INCLUDES) file.c $(LIB) -o file.o $(CCFLAGS)

fork:
	$(CCC) $(INCLUDES) fork.c $(LIB) -o fork.o $(CCFLAGS)

pipe:
	$(CCC) $(INCLUDES) pipe.c $(LIB) -o pipe.o $(CCFLAGS)

std:
	$(CCC) $(INCLUDES) std.c $(LIB) -o std.o $(CCFLAGS)

tcp-client:
	$(CCC) $(INCLUDES) tcp-client.c $(LIB) -o tcp-client.o $(CCFLAGS)

tcp-server:
	$(CCC) $(INCLUDES) tcp-server.c $(LIB) -o tcp-server.o $(CCFLAGS)

clean:
	rm -f *.o
