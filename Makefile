CC := gcc

SRC := src
BIN := binaries

FLAGS := -Isrc

OBJECTS := ${BIN}/main.o		\
		   ${BIN}/logger.o 		\
		   ${BIN}/protocol.o	\
		   ${BIN}/x86_io.o

${BIN}/sc-emulator: ${OBJECTS}
	${CC} ${OBJECTS} -o ${BIN}/sc-emulator

${BIN}/main.o: ${SRC}/main.c
	${CC} ${FLAGS} -c ${SRC}/main.c -o ${BIN}/main.o

${BIN}/logger.o: ${SRC}/core/logger.c
	${CC} ${FLAGS} -c ${SRC}/core/logger.c -o ${BIN}/logger.o

${BIN}/protocol.o: ${SRC}/protocol/protocol.c
	${CC} ${FLAGS} -c ${SRC}/protocol/protocol.c -o ${BIN}/protocol.o

${BIN}/x86_io.o: ${SRC}/hal/x86_io.c
	${CC} ${FLAGS} -c ${SRC}/hal/x86_io.c -o ${BIN}/x86_io.o

clean:
	rm -f ${BIN}/*.o
