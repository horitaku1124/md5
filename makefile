CC = gcc
CFLG = -std=c99 -c -g -pg -Wall -Wextra
LDFLG = -pg
SRC = main.c md5.c
OBJ = $(SRC:.c=.o)
EXE = a.out

${EXE}: ${OBJ}
	${CC} ${OBJ} ${LDFLG} 

${OBJ}: ${SRC}
	${CC} ${CFLG} $?
 
run:
	./${EXE}
 
clear:
	rm ${OBJ} ${EXE}
