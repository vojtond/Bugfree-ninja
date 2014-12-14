projekt: main.o ial.o scanner.o vyraz.o str.o interpret.o lin_seznam.o
	gcc main.o ial.o scanner.o vyraz.o str.o interpret.o lin_seznam.o -o projekt
	
	
main.o: main.c parser.h
	gcc main.c -c

ial.o: ial.c ial.h
	gcc ial.c -c

scanner.o: scanner.c scanner.h
	gcc scanner.c -c

vyraz.o: vyraz.c vyraz.h
	gcc vyraz.c -c
	
str.o: str.c str.h
	gcc str.c -c
	
Interpret.o: interpret.c interpret.h
	gcc interpret.c -c
	
lin.seznam.o: lin_seznam.c lin_seznam.h
	gcc lin_seznam.c -c