all:malloc_2 alloc_1 alloc_more manager read

malloc_2: malloc_2.o
	gcc -o malloc_2 malloc_2.o -lm -lpthread -lpmem 

alloc_1: alloc_1.o
	gcc -o alloc_1 alloc_1.o -lm -lpthread -lpmem -lpmemobj

alloc_more: alloc_more.o
	gcc -o alloc_more alloc_more.o -lm -lpthread -lpmem -lpmemobj

manager: manager.o
	gcc -o manager manager.o -lm -lpthread -lpmem

read: read.o
	gcc -o read read.o -lm -lpthread -lpmem

malloc_2.o :
	gcc -c malloc_2.c

alloc_1.o: alloc_1.c
	gcc -c alloc_1.c

alloc_more.o: alloc_more.c
	gcc -c alloc_more.c

manager.o: manager.c
	gcc -c manager.c

read.o: read.c
	gcc -c read.c

clean:
	rm -rf *.o



