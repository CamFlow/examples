INCLUDES = -I/usr/include
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = -lprovenance -lpthread -lz

compile_reader:
	$(CCC) $(INCLUDES) reader.c $(LIB) -o reader.o $(CCFLAGS)

compile_writer:
	$(CCC) $(INCLUDES) writer.c $(LIB) -o writer.o $(CCFLAGS)

compile: compile_reader compile_writer

clean:
	rm -f *.o

all: compile

run:
	./writer.o &
	sudo ./reader.o &
