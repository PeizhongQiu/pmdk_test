
CC = cc
CP = cp
RM = rm -f
MV = mv -f

LDFLAGS = -lm -lpthread -lrt -lpmem -lpmemobj

EXE_FILES = alloc_1 alloc_more
 
all: ${EXE_FILES}
ALLOC_1_OBJ=alloc_1.o
ALLOC_MORE_OBJ=alloc_more.o


OBJS = alloc_1.o alloc_more.o 

alloc_1.o: alloc_1.c
	${CC} -Wall -D_FILE_OFFSET_BITS=64 -g -c alloc_1.c

alloc_more.o: alloc_more.c
	${CC} -Wall -D_FILE_OFFSET_BITS=64 -g -c alloc_more.c

alloc_1: alloc_1.o
	${CC} -Wall -D_FILE_OFFSET_BITS=64  -O2 -g -o $@ ${ALLOC_1_OBJ} ${LDFLAGS} 

alloc_more: alloc_more.o
	${CC} -Wall -D_FILE_OFFSET_BITS=64  -O2 -g -o $@ ${ALLOC_MORE_OBJ} ${LDFLAGS} 

clean:
	${RM} *.o core ~* *.cpp ${EXE_FILES}
