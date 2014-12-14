projekt: main.o ial.o scanner.o vyraz.o str.o Interpret.o lin.seznam.o
	gcc main.o ial.o scanner.o vyraz.o str.o Interpret.o lin.seznam.o -o projekt
	
	
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
	
Interpret.o: Interpret.c Interpret.h
	gcc Interpret.c -c
	
lin.seznam.o: lin.seznam.c lin.seznam.h
	gcc lin.seznam.c -c