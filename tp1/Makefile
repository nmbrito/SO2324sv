# Notes
# $^ -> All parameters
# $< -> One parameter
# $@ -> Label
# target: prerequisites
# OBJS = $(SRCS:%=$(OBJECTS_DIR)/%.o)
# $(CC) $(CFLAGS) -c $^ -o $@ $(EXTRAFLAGS)

# Compiler settings
# -Wall		verbose compiler warnings
# -g		compile with debug information
CC 		    = gcc
CFLAGS  	= -Wall
CFLAGS     += -g
EXTRAFLAGS  = -lm

# Directories
SOURCES_DIR = ./src
OBJECTS_DIR = ./.objects
TARGETS_DIR = ./targets

# Make directories
MD		 = mkdir
MDFLAGS	+= -p

# Objects (.o)
OBJS_CPU_STRESS   	   = $(OBJECTS_DIR)/cpu_stress.o
OBJS_EXERCISE2    	   = $(OBJECTS_DIR)/exercise2.o
OBJS_COUNT_WORDS  	   = $(OBJECTS_DIR)/count_words.o
OBJS_EXERCISE4    	   = $(OBJECTS_DIR)/exercise4.o
OBJS_VECTOR_STAT_PROC  = $(OBJECTS_DIR)/vector_stat_proc.o
OBJS_VECTOR_STAT_PROC += $(OBJECTS_DIR)/vector_stat_proc_utils.o

# Dependencies (.c)
DEPS_CPU_STRESS        = $(SOURCES_DIR)/cpu_stress.c
DEPS_EXERCISE2         = $(SOURCES_DIR)/exercise2.c
DEPS_COUNT_WORDS       = $(SOURCES_DIR)/count_words.c
DEPS_EXERCISE4         = $(SOURCES_DIR)/exercise4.c
DEPS_VECTOR_STAT_PROC  = $(SOURCES_DIR)/vector_stat_proc.c
DEPS_VECTOR_STAT_PROC += $(SOURCES_DIR)/vector_stat_proc_utils.c

# Rules - DON'T CHANGE -------------------------------------{{{1
all: createdir cpu_stress exercise2 count_words exercise4 vector_stat_proc

# cpu_stress ---------------------------------------------- {{{2
cpu_stress : $(OBJS_CPU_STRESS)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# --------------------------------------------------------- 2}}}

# exercise2 ----------------------------------------------- {{{2
exercise2 : $(OBJS_EXERCISE2)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# --------------------------------------------------------- 2}}}

# count_words --------------------------------------------- {{{2
count_words : $(OBJS_COUNT_WORDS)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# --------------------------------------------------------- 2}}}

# exercise4 ----------------------------------------------- {{{2
exercise4 : $(OBJS_EXERCISE4)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# --------------------------------------------------------- 2}}}

# vector_stat_proc ---------------------------------------- {{{2
vector_stat_proc : $(OBJS_VECTOR_STAT_PROC)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# --------------------------------------------------------- 2}}}

# make directories ---------------------------------------- {{{2
createdir:
	$(MD) $(MDFLAGS) $(OBJECTS_DIR)
	$(MD) $(MDFLAGS) $(TARGETS_DIR)
# --------------------------------------------------------- 2}}}

# clean --------------------------------------------------- {{{2
clean:
	rm -f $(OBJECTS_DIR)/*.o
	rm -f $(TARGETS_DIR)/*
# --------------------------------------------------------- 2}}}
# --------------------------------------------------------- 1}}}
