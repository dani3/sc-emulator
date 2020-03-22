CC=gcc
SRC=src
OUT=binaries

INC=-Isrc

${OUT}/sc-emulator: ${OUT}/main.o ${OUT}/logger.o
	${CC} ${OUT}/main.o ${OUT}/logger.o -o ${OUT}/sc-emulator

${OUT}/main.o: ${SRC}/main.c
	${CC} ${INC} -c ${SRC}/main.c -o ${OUT}/main.o

${OUT}/logger.o: ${SRC}/core/logger.c
	${CC} ${INC} -c ${SRC}/core/logger.c -o ${OUT}/logger.o

clean:
	rm -f ${OUT}/*.o
