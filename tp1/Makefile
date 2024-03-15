# Remember:
# $^ -> All parameters
# $< -> One parameter
# $@ -> Label
 
# C compiler & flags
CC=gcc
CFLAGS=-Wall 	\
	   -g		\
	   -lm

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
	$(CC) $(CFLAGS) -c $^
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
	rm -f *.o
	rm -f exer1
	rm -f exer2
	rm -f exer3
	rm -f exer4
