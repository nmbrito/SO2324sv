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
EXER2DEPS= 1.2.c
EXER3DEPS= 1.3.c
EXER4DEPS= 1.3.c

# exercises objects
CPU_STRESS_OBJS= cpu_stress.o
EXER2OBJS= exer2.o
EXER3OBJS= exer3.o
EXER4OBJS= exer4.o

%.o: %.c
	$(CC) $(CFLAGS) -c $^

all: cpu_stress exer2 exer3 exer4

cpu_stress: $(CPU_STRESS_OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

cpu_stress.o: $(CPU_STRESS_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

exer2: $(EXER2OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

exer2.o: $(EXER2DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

exer3: $(EXER3OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

exer3.o: $(EXER3DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

exer4: $(EXER4OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(EXTRAFLAGS)

exer4.o: $(EXER4DEPS)
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -f *.o
	rm -f cpu_stress
	rm -f exer2
	rm -f exer3
	rm -f exer4
