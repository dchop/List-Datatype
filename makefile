CFLAGS = -g -W -Wall -Wpedantic
SRC = ./src/list.c
TEST = ./tests/test1.c
INC = -I include
BIN = bin/output

all: clean build

build: list.o test1.o
	@mkdir -p bin
	gcc $(CFLAGS) list.o test1.o -o $(BIN)

test1.o: $(TEST)
	gcc -c $(CFLAGS) $(INC) $(TEST)

list.o: $(SRC)
	gcc -c $(CFLAGS) $(INC) $(SRC)

clean:
	rm -f *.o* *.out* $(BIN)

mem: clean build mem-check

mem-check:
	@mkdir -p bin 
	valgrind --leak-check=full ./$(BIN)