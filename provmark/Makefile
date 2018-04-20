INCLUDES = -I/usr/include
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = -lprovenance -lpthread -lz

.SUFFIXES: .c

all: open empty

open:
	$(CCC) $(INCLUDES) open.c $(LIB) -o open.o $(CCFLAGS)

empty:
	$(CCC) $(INCLUDES) empty.c $(LIB) -o empty.o $(CCFLAGS)

clean:
	rm -f *.o
