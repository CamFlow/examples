INCLUDES = -I/usr/include
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = -lprovenance -lpthread -lz

.SUFFIXES: .c

all: many_read many_read_one_write many_read_one_stat many_read_socket_things

many_read:
	$(CCC) $(INCLUDES) many_read.c $(LIB) -o many_read.o $(CCFLAGS)

many_read_one_write:
	$(CCC) $(INCLUDES) many_read_and_write.c $(LIB) -o many_read_and_write.o $(CCFLAGS)

many_read_one_stat:
	$(CCC) $(INCLUDES) many_read_and_stat.c $(LIB) -o many_read_and_stat.o $(CCFLAGS)

many_read_socket_things:
	$(CCC) $(INCLUDES) many_read_socket_things.c $(LIB) -o many_read_socket_things.o $(CCFLAGS)

clean:
	rm -f *.o
