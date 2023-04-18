paint.out: main.o paint.o
	gcc -g -Wall -Werror -o paint.out main.o paint.o -lm

main.o: main.c paint.h
	gcc -g -Wall -c -o main.o main.c -lm

paint.o: paint.c paint.c
	gcc -g -Wall -Werror -c -o paint.o paint.c -lm

clean:
	rm -f *.o *.out -lm