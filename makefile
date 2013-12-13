CC = gcc
CFLG = -std=c99 -c -g -pg -Wall -Wextra
LDFLG = -pg
SRC = main.c md5.c
SRC2 = main2.c md5.c
OBJ = $(SRC:.c=.o)
OBJ2= $(SRC2:.c=.o)
EXE = main
EXE2 = main2

${EXE2}: ${OBJ2}
	${CC} ${OBJ2} ${LDFLG} -o ${EXE2}

${EXE}: ${OBJ}
	${CC} ${OBJ} ${LDFLG} -o ${EXE}

${OBJ}: ${SRC}
	${CC} ${CFLG} $?
 
run:
	./${EXE}
 
clear:
	rm ${OBJ} ${EXE}

test:
	./hash_test.sh a 0cc175b9c0f1b6a831c399e269772661
	./hash_test.sh abc 900150983cd24fb0d6963f7d28e17f72
	./hash_test.sh aBg0 e03c7e0d92db165c6dce85d09fade8c0
	./hash_test.sh "!#%0" ba4e3039000b75cdb787b18d2ea86d4b
	./hash_test.sh aaaaaaaaaaaaaaaa 23ca472302f49b3ea5592b146a312da0
	./hash_test.sh asdighaiosudhgaiosuhd 278c9f8f960bbfd0f336d312c9bcafb6
	./hash_test.sh Sy9cDeMK fcb2ca343b5b3751fb8b22ec146d4c2c
	./hash_test.sh n3RPCF6ct/,kL!L.!, eabcbb8cde94de1081e1ccd549cad06c
	./hash_test.sh t8Wfnv5XWn2rwaVdYKPcEqFpJ2sXC848jS4DNkGU df0436859b91bddcdef409ff71b64e21
	echo "\n\n All Fine :) \n\n"