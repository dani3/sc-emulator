CC=gcc
SRC=src
OUT=binaries

${OUT}/sc-emulator: ${OUT}/main.o
	${CC} ${OUT}/main.o -o ${OUT}/sc-emulator

${OUT}/main.o: ${SRC}/main.c
	${CC} -c ${SRC}/main.c -o ${OUT}/main.o

clean:
	rm ${OUT}/*.o
