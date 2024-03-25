# Remember:
# $^ -> All parameters
# $< -> One parameter
# $@ -> Label
 
# C compiler & flags
CC=gcc
CFLAGS=-Wall 	\
	   -g
EXTRAFLAGS=-lm

# exercises dependencies
VECTOR_STAT_PROC_DEPS=vector_stat_proc.c utilities.c

# exercises objects
VECTOR_STAT_PROC_OBJS=vector_stat_proc.o utilities.o

#%.o: %.c
#	$(CC) $(CFLAGS) -c $^

all: vector_stat_proc

vector_stat_proc: $(VECTOR_STAT_PROC_DEPS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

vector_stat_proc.o: $(VECTOR_STAT_PROC_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f cpu_stress
	rm -f 2_consider
	rm -f count_words
	rm -f 4_consider
