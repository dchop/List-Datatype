output: list.o sampleTest.o
	gcc -g -W -Wall -Wpedantic list.o sampleTest.o -o output
list: list.o test.o
	gcc -g -W -Wall -Wpedantic list.o test.o -o output
sampleTest.o: sampleTest.c
	gcc -c -g -W -Wall -Wpedantic sampleTest.c
test.o: test.c
	gcc -c -g -W -Wall -Wpedantic test.c
list.o: list.c
	gcc -c -g -W -Wall -Wpedantic list.c
clean:
	rm -f *.o* output test