output: list.o sampleTest.o
	gcc -g -W -Wall -Wpedantic list.o sampleTest.o -o output
list: list.o test.o
	gcc -g -W -Wall -Wpedantic list.o test.o -o output
myTest: list.o myTest.o
	gcc -g -W -Wall -Wpedantic list.o myTest.o -o output
timTest: list.o timTest.o
	gcc -g -W -Wall -Wpedantic list.o timTest.o -o output
sampleTest.o: sampleTest.c
	gcc -c -g -W -Wall -Wpedantic sampleTest.c
myTest.o: myTest.c
	gcc -c -g -W -Wall -Wpedantic myTest.c
test.o: test.c
	gcc -c -g -W -Wall -Wpedantic test.c
list.o: list.c
	gcc -c -g -W -Wall -Wpedantic list.c
timTest.o: timTest.c
	gcc -c -g -W -Wall -Wpedantic timTest.c
clean:
	rm -f *.o* output test