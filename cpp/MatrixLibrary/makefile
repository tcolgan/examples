# makefile for matrix.exe

#project specific stuff

OUT=matrix.exe
SRCS=       \
 matrix.cpp \
 main.cpp

#generic stuff

OBJS := $(SRCS:.cpp=.o)
CPP = g++
DEPEND= makedepend $(CFLAGS)
#CFLAGS= -O
#LDFLAGS= -s
#CFLAGS= -O -Wall
#LDFLAGS= -s -Wall

all: $(OUT)

run: 
	./$(OUT) matA.txt maty.txt

$(SRCS):
	$(CPP) $(CFLAGS) -c $*.c

$(OUT): $(OBJS)
	$(CPP) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm *.o 
	rm *.exe

depend: $(SRCS)
	$(DEPEND) $(SRCS)
   
   
   
   
# DO NOT DELETE

matrix.o: matrix.h /usr/include/memory.h /usr/include/string.h
matrix.o: /usr/include/_ansi.h /usr/include/newlib.h
matrix.o: /usr/include/sys/config.h /usr/include/machine/ieeefp.h
matrix.o: /usr/include/sys/reent.h /usr/include/sys/_types.h
matrix.o: /usr/include/sys/lock.h /usr/include/sys/string.h
main.o: matrix.h
