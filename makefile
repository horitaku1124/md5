CC = gcc
CFLG = -std=c99  -c -g -pg -Wall -Wextra
LDFLG = -pg
SRC = main.c md5.c
SRC2 = main2.c md5.c
SRC3 = crack1.c md5.c
OBJ = $(SRC:.c=.o)
OBJ2= $(SRC2:.c=.o)
OBJ3= $(SRC3:.c=.o)
EXE = main
EXE2 = main2
EXE3 = crack1
EXE4 = main3

TEST_MAIN2=./tester.sh ./main2
TEST_MAIN3=./tester.sh ./main3

${EXE4}: md5
	${CC} ${CFLG} main3.c md5.c
	${CC} main3.o md5.o -pg -o main3

${EXE3}: md5 obj_crack
	${CC} crack1.o md5.o -pg -o crack1

${EXE2}: ${OBJ}
	${CC} ${CFLG} main2.c md5.c
	${CC} main2.o md5.o -pg -o main2

${EXE}: ${OBJ}
	${CC} ${OBJ} ${LDFLG} -o ${EXE}

${OBJ}: ${SRC}
	${CC} ${CFLG} $?

md5:
	${CC} ${CFLG} md5.c

obj_crack:
	${CC} ${CFLG} crack1.c

run:
	./${EXE}
 
clean:
	-rm *.o ${EXE} ${EXE2} ${EXE3} ${EXE4}

test:  ${EXE2}
	${TEST_MAIN2} a 0cc175b9c0f1b6a831c399e269772661
	${TEST_MAIN2} abc 900150983cd24fb0d6963f7d28e17f72
	${TEST_MAIN2} aBg0 e03c7e0d92db165c6dce85d09fade8c0
	${TEST_MAIN2} "!#%0" ba4e3039000b75cdb787b18d2ea86d4b
	${TEST_MAIN2} aaaaaaaaaaaaaaaa 23ca472302f49b3ea5592b146a312da0
	${TEST_MAIN2} asdighaiosudhgaiosuhd 278c9f8f960bbfd0f336d312c9bcafb6
	${TEST_MAIN2} Sy9cDeMK fcb2ca343b5b3751fb8b22ec146d4c2c
	${TEST_MAIN2} n3RPCF6ct/,kL!L.!, eabcbb8cde94de1081e1ccd549cad06c
	${TEST_MAIN2} t8Wfnv5XWn2rwaVdYKPcEqFpJ2sXC848jS4DNkGU df0436859b91bddcdef409ff71b64e21


test2: ${EXE4}
	${TEST_MAIN3}  a 0cc175b9c0f1b6a831c399e269772661
	${TEST_MAIN3} abc 900150983cd24fb0d6963f7d28e17f72
	${TEST_MAIN3} aBg0 e03c7e0d92db165c6dce85d09fade8c0
	${TEST_MAIN3} "!#%0" ba4e3039000b75cdb787b18d2ea86d4b
	${TEST_MAIN3} aaaaaaaaaaaaaaaa 23ca472302f49b3ea5592b146a312da0
	${TEST_MAIN3} asdighaiosudhgaiosuhd 278c9f8f960bbfd0f336d312c9bcafb6
	${TEST_MAIN3} Sy9cDeMK fcb2ca343b5b3751fb8b22ec146d4c2c
	${TEST_MAIN3} n3RPCF6ct/,kL!L.!, eabcbb8cde94de1081e1ccd549cad06c
	${TEST_MAIN3} t8Wfnv5XWn2rwaVdYKPcEqFpJ2sXC848jS4DNkGU df0436859b91bddcdef409ff71b64e21
	
