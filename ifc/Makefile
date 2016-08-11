INCLUDES = -I/usr/local/include
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = /usr/local/lib/ifclib.a

.SUFFIXES: .c

all: simple bridge pipe file msg self

simple:
	$(CCC) $(INCLUDES) simple.c $(LIB) -o simple.o $(CCFLAGS)

bridge:
	$(CCC) $(INCLUDES) bridge.c $(LIB) -o bridge.o $(CCFLAGS)

pipe:
	$(CCC) $(INCLUDES) pipe.c $(LIB) -o pipe.o $(CCFLAGS)

file:
	$(CCC) $(INCLUDES) file.c $(LIB) -o file.o $(CCFLAGS)

msg:
	$(CCC) $(INCLUDES) msg.c $(LIB) -o msg.o $(CCFLAGS)

self:
	$(CCC) $(INCLUDES) self.c $(LIB) -o self.o $(CCFLAGS)

debug: debug_simple debug_bridge debug_pipe debug_msg debug_self

debug_simple:
	$(CCC) $(INCLUDES) simple.c $(LIB) -o simple.o $(CCFLAGS) -g

debug_bridge:
	$(CCC) $(INCLUDES) bridge.c $(LIB) -o bridge.o $(CCFLAGS) -g

debug_pipe:
	$(CCC) $(INCLUDES) pipe.c $(LIB) -o pipe.o $(CCFLAGS) -g

debug_file:
	$(CCC) $(INCLUDES) file.c $(LIB) -o file.o $(CCFLAGS) -g

debug_msg:
	$(CCC) $(INCLUDES) msg.c $(LIB) -o msg.o $(CCFLAGS) -g

debug_self:
	$(CCC) $(INCLUDES) self.c $(LIB) -o self.o $(CCFLAGS) -g

clean:
	rm -f *.o
