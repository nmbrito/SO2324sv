# Notes
# $^ -> All parameters
# $< -> One parameter
# $@ -> Label
# target: prerequisites
# OBJS = $(SRCS:%=$(OBJECTS_DIR)/%.o)

	#$(CC) $(CFLAGS) -c $^ -o $@ $(EXTRAFLAGS)
# Compiler settings
# -Wall		verbose compiler warnings
# -g		compile with debug information
CC		    = gcc
CFLAGS	    = -Wall
CFLAGS	   += -g
EXTRAFLAGS  = -lm

# Directories
SOURCES_DIR = ./src
OBJECTS_DIR = ./.objects
TARGETS_DIR = ./targets

# Objects (.o)
OBJS_EXERCISE1			 = $(OBJECTS_DIR)/exercise1.o
OBJS_CPU_STRESS			 = $(OBJECTS_DIR)/cpu_stress.o
OBJS_VECTOR_STAT_PROC    = $(OBJECTS_DIR)/vector_stat_proc.o
OBJS_VECTOR_STAT_PROC   += $(OBJECTS_DIR)/vector_stat_proc-utils.o
OBJS_VECTOR_STAT_SERVER  = $(OBJECTS_DIR)/vector_stat_server.o
OBJS_VECTOR_STAT_SERVER	+= $(OBJECTS_DIR)/vector_stat_server-utils.o
OBJS_EXERCISE7			 = $(OBJECTS_DIR)/exercise7.o

# Dependencies (.c)
DEPS_EXERCISE1			 = $(SOURCES_DIR)/exercise1.c
DEPS_CPU_STRESS			 = $(SOURCES_DIR)/cpu_stress.c
DEPS_VECTOR_STAT_PROC    = $(SOURCES_DIR)/vector_stat_proc.c
DEPS_VECTOR_STAT_PROC   += $(SOURCES_DIR)/vector_stat_proc-utils.c
DEPS_VECTOR_STAT_SERVER  = $(SOURCES_DIR)/vector_stat_server.c
DEPS_VECTOR_STAT_SERVER	+= $(SOURCES_DIR)/vector_stat_server-utils.c
DEPS_EXERCISE7			 = $(SOURCES_DIR)/exercise7.c

# Rules - DON'T CHANGE -------------------------------------{{{1
all: exercise1 cpu_stress vector_stat_proc vector_stat_server exercise7

# exercise1 ----------------------------------------------- {{{2
exercise1 : $(OBJS_EXERCISE1)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# --------------------------------------------------------- 2}}}

# cpu_stress ---------------------------------------------- {{{2
cpu_stress : $(OBJS_CPU_STRESS)
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

# vector_stat_server -------------------------------------- {{{2
vector_stat_server : $(OBJS_VECTOR_STAT_SERVER)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 
# --------------------------------------------------------- 2}}}

# exercise7 ----------------------------------------------- {{{2
exercise7 : $(OBJS_EXERCISE7)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# --------------------------------------------------------- 2}}}

# clean --------------------------------------------------- {{{2
clean:
	rm -f $(OBJECTS_DIR)/*.o
	rm -f $(TARGETS_DIR)/*
# --------------------------------------------------------- 2}}}
# --------------------------------------------------------- 1}}}
