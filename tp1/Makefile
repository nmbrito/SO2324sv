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
EXER1DEPS= .c
EXER2DEPS= .c
EXER3DEPS= .c
EXER4DEPS= .c

# exercises objects
EXER1OBJS= .o
EXER2OBJS= .o
EXER3OBJS= .o
EXER4OBJS= .o

%.o: %.c
	$(CC) $(CFLAGS) -c $^

all: exer1 exer2 exer3 exer4

exer1: $(EXER1OBJS)
	echo "Compiling exercise 1"
	$(CC) $(CFLAGS) $< -o $@  

exer1.o: $(EXER1DEPS)
	$(CC) $(CFLAGS) -c $< -o $@  

exer2: $(EXER2OBJS)
	$(CC) $(CFLAGS) $< -o $@  

exer2.o: $(EXER2DEPS)
	$(CC) $(CFLAGS) -c $< -o $@  

exer3: $(EXER3OBJS)
	$(CC) $(CFLAGS) $< -o $@  

exer3.o: $(EXER3DEPS)
	$(CC) $(CFLAGS) -c $< -o $@  

exer4: $(EXER4OBJS)
	$(CC) $(CFLAGS) $< -o $@  

exer4.o: $(EXER4DEPS)
	$(CC) $(CFLAGS) -c $< -o $@  



clean:
	rm -f *.o
	rm -f exer1
	rm -f exer2
	rm -f exer3
	rm -f exer4
