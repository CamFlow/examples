INCLUDES = -I/usr/local/include
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = /usr/local/lib/provenancelib.a -lpthread

.SUFFIXES: .c

all: exec file fork pipe std

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

debug: debug_simple debug_bridge debug_pipe debug_msg debug_self debug_exec

debug_exec:
	$(CCC) $(INCLUDES) exec.c $(LIB) -o exec.o $(CCFLAGS) -g

debug_file:
	$(CCC) $(INCLUDES) file.c $(LIB) -o file.o $(CCFLAGS) -g

debug_fork:
	$(CCC) $(INCLUDES) fork.c $(LIB) -o fork.o $(CCFLAGS) -g

debug_pipe:
	$(CCC) $(INCLUDES) pipe.c $(LIB) -o pipe.o $(CCFLAGS) -g

debug_std:
	$(CCC) $(INCLUDES) std.c $(LIB) -o std.o $(CCFLAGS) -g

clean:
	rm -f *.o
