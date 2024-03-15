# C compiler & flags
CC=gcc
CFLAGS=-Wall \
	   -g

# exercises dependencies
EXER1DEPS=
EXER2DEPS=
EXER3DEPS=
EXER4DEPS=

# exercises objects
EXER1OBJS=
EXER2OBJS=
EXER3OBJS=
EXER4OBJS=

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
all:

exer1: $(EXER1OBJS)
	echo "Compiling exercise 1"
	$(CC) -o $@ $< $(CFLAGS)
exer1.o:

exer2:
exer2.o:

exer3:
exer3.o:

exer4:
exer4.o:


clean:
	rm -rf *.o
