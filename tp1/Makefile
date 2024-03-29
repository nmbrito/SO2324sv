# Remember:
# $^ -> All parameters
# $< -> One parameter
# $@ -> Label
 
# C COMPILER & FLAGS
CC=gcc
CFLAGS=-Wall 	\
	   -g
EXTRAFLAGS=-lm

# EXERCISES DEPENDENCIES
CPU_STRESS_DEPS= cpu_stress.c
2CONSIDER_DEPS= 2_consider.c
COUNT_WORDS_DEPS= count_words.c
4CONSIDER_DEPS= 4_consider.c
VECTOR_STAT_PROC_DEPS=./vectorstat/vector_stat_proc.c ./vectorstat/utilities.c ./vectorstat/child.c

# EXERCISES OBJECTS
CPU_STRESS_OBJS= cpu_stress.o
2CONSIDER_OBJS= 2_consider.o
COUNT_WORDS_OBJS= count_words.o
4CONSIDER_OBJS= 4_consider.o
VECTOR_STAT_PROC_OBJS=./vectorstat/vector_stat_proc.o ./vectorstat/utilities.o ./vectorstat/child.o

#%.o: %.c
#	$(CC) $(CFLAGS) -c $^

# BUILD ALL
all: cpu_stress 2_consider count_words 4_consider vector_stat_proc

# BUILD CPU_STRESS
cpu_stress: $(CPU_STRESS_OBJS)
	$(CC) $(CFLAGS) $< -o output/$@ $(EXTRAFLAGS)

cpu_stress.o: $(CPU_STRESS_DEPS)
	$(CC) $(CFLAGS) -c $< -o output/$@

# BUILD EXERCISE 2
2_consider: $(2CONSIDER_OBJS)
	$(CC) $(CFLAGS) $< -o output/$@ $(EXTRAFLAGS)

2_consider.o: $(2CONSIDER_DEPS)
	$(CC) $(CFLAGS) -c $< -o output/$@

# BUILD COUNT_WORDS
count_words: $(COUNT_WORDS_OBJS)
	$(CC) $(CFLAGS) $< -o output/$@ $(EXTRAFLAGS)

count_words.o: $(COUNT_WORDS_DEPS)
	$(CC) $(CFLAGS) -c $< -o output/$@

# BUILD EXERCISE 4
4_consider: $(4CONSIDER_OBJS)
	$(CC) $(CFLAGS) $< -o output/$@ $(EXTRAFLAGS)

4_consider.o: $(4CONSIDER_DEPS)
	$(CC) $(CFLAGS) -c $< -o output/$@
	
# BUILD VECTOR_STAT_PROC
vector_stat_proc: $(VECTOR_STAT_PROC_DEPS)
	$(CC) $(CFLAGS) $^ -o output/$@ $(EXTRAFLAGS)

vector_stat_proc.o: $(VECTOR_STAT_PROC_DEPS)
	$(CC) $(CFLAGS) -c $^ -o output/$@

# CLEAN
clean:
	rm -f output/*.o
	rm -f output/cpu_stress
	rm -f output/2_consider
	rm -f output/count_words
	rm -f output/4_consider
	rm -f output/vector_stat_proc
