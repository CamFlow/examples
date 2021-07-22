INCLUDES = -I/usr/include
CCFLAGS = -g -O2 -fpic
CCC = gcc
LIB = -lprovenance -lpthread -lz

compile_evil_file:
	$(CCC) $(INCLUDES) evil_file.c $(LIB) -o evil_file.o $(CCFLAGS)

compile_my_file:
	$(CCC) $(INCLUDES) my_file.c $(LIB) -o my_file.o $(CCFLAGS)

compile_overwrite:
	$(CCC) $(INCLUDES) overwrite.c $(LIB) -o overwrite.o $(CCFLAGS)

compile: compile_evil_file compile_my_file compile_overwrite

clean:
	rm -f *.o

all: compile

run:
	./writer.o &
	sudo ./reader.o &
