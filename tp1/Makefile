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
CPU_STRESS_DEPS= cpu_stress.c
2CONSIDER_DEPS= 2_consider.c
COUNT_WORDS_DEPS= count_words.c
4CONSIDER_DEPS= 4_consider.c
VECTOR_STAT_PROC_DEPS=./vectorstat/vector_stat_proc.c ./vectorstat/utilities.c ./vectorstat/child.c

# exercises objects
CPU_STRESS_OBJS= cpu_stress.o
2CONSIDER_OBJS= 2_consider.o
COUNT_WORDS_OBJS= count_words.o
4CONSIDER_OBJS= 4_consider.o
VECTOR_STAT_PROC_OBJS=./vectorstat/vector_stat_proc.o ./vectorstat/utilities.o ./vectorstat/child.o

#%.o: %.c
#	$(CC) $(CFLAGS) -c $^

all: cpu_stress 2_consider count_words 4_consider vector_stat_proc

cpu_stress: $(CPU_STRESS_OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

cpu_stress.o: $(CPU_STRESS_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

2_consider: $(2CONSIDER_OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

2_consider.o: $(2CONSIDER_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

count_words: $(COUNT_WORDS_OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

count_words.o: $(COUNT_WORDS_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

4_consider: $(4CONSIDER_OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

4_consider.o: $(4CONSIDER_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	
vector_stat_proc: $(VECTOR_STAT_PROC_DEPS)
	$(CC) $(CFLAGS) $^ -o $@ $(EXTRAFLAGS)

vector_stat_proc.o: $(VECTOR_STAT_PROC_DEPS)
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o
	rm -f cpu_stress
	rm -f 2_consider
	rm -f count_words
	rm -f 4_consider
