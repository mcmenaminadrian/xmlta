default: all

all: xmlta

clean:
	rm -f *.o


xmlta: xmlta.o
	gcc -o xmlta xmlta.o -lexpat

xmlta.o: xmlta.c
	gcc -O2 -o xmlta.o -c -Wall xmlta.c 
