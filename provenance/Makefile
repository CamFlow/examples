INCLUDES = -I/usr/include
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = -lprovenance -lpthread -lz

.SUFFIXES: .c

all: exec file fork pipe std mmap mmap2 tcp-client tcp-server print unix id thread many_write

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

mmap:
	$(CCC) $(INCLUDES) mmap.c $(LIB) -o mmap.o $(CCFLAGS)

mmap2:
	$(CCC) $(INCLUDES) mmap2.c $(LIB) -o mmap2.o $(CCFLAGS)

tcp-client:
	$(CCC) $(INCLUDES) tcp-client.c $(LIB) -o tcp-client.o $(CCFLAGS)

tcp-server:
	$(CCC) $(INCLUDES) tcp-server.c $(LIB) -o tcp-server.o $(CCFLAGS)

print:
	$(CCC) $(INCLUDES) print.c $(LIB) -o print.o $(CCFLAGS)

unix:
	$(CCC) $(INCLUDES) unix-socket.c $(LIB) -o unix-socket.o $(CCFLAGS)

id:
	$(CCC) $(INCLUDES) id.c $(LIB) -o id.o $(CCFLAGS)

thread:
	$(CCC) $(INCLUDES) thread.c $(LIB) -o thread.o $(CCFLAGS)

many_write:
	$(CCC) $(INCLUDES) many_write.c $(LIB) -o many_write.o $(CCFLAGS)

clean:
	rm -f *.o
