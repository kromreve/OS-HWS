CFLAGS = -g -Wall

CC = g++


TARGET = HWS

${TARGET}: ${TARGET}.o 
	${CC} ${CFLAGS} -o ${TARGET} ${TARGET}.o
${TARGET}.o: ${TARGET}.cpp ${TARGET}.hpp
	${CC} ${CFLAGS} -c ${TARGET}.cpp
  
clean:
	if [ -f *.o ]; then rm *.o; fi
	if [ -f HWS ]; then rm HWS; fi
