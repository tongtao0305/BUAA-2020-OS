fibo: main.o fibo.o
	gcc main.o fibo.o -o ../fibo 

main.o: main.c fibo.c ../include/fibo.h
	gcc -I ../include -c main.c -o main.o

fibo.o: fibo.c ../include/fibo.h
	gcc -I../include -c fibo.c -o fibo.o

clean:
	rm -f *.o
