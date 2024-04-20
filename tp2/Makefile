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
OBJS_CPU_INFO 			 	 = $(OBJECTS_DIR)/cpu_info.o
OBJS_CPU_STRESS_THREADS		 = $(OBJECTS_DIR)/cpu_stress_threads.o
OBJS_VECTOR_STAT_PROC   	 = $(OBJECTS_DIR)/vector_stat_proc.o
OBJS_VECTOR_STAT_PROC   	+= $(OBJECTS_DIR)/vector_stat_proc-utils.o
OBJS_VECTOR_STAT_SERVER 	 = $(OBJECTS_DIR)/vector_stat_server.o
OBJS_VECTOR_STAT_SERVER		+= $(OBJECTS_DIR)/vector_stat_server-utils.o
OBJS_EXERCISE7				 = $(OBJECTS_DIR)/exercise7.o

# Dependencies (.c)
DEPS_CPU_INFO 				 = $(SOURCES_DIR)/cpu_info.c
DEPS_CPU_STRESS_THREADS		 = $(SOURCES_DIR)/cpu_stress_threads.c
DEPS_VECTOR_STAT_PROC   	 = $(SOURCES_DIR)/vector_stat_proc.c
DEPS_VECTOR_STAT_PROC   	+= $(SOURCES_DIR)/vector_stat_proc-utils.c
DEPS_VECTOR_STAT_SERVER 	 = $(SOURCES_DIR)/vector_stat_server.c
DEPS_VECTOR_STAT_SERVER		+= $(SOURCES_DIR)/vector_stat_server-utils.c
DEPS_EXERCISE7				 = $(SOURCES_DIR)/exercise7.c

# Rules - DON'T CHANGE -------------------------------------{{{1
all: cpu_info cpu_stress_threads vector_stat_proc vector_stat_server exercise7

# cpu_info ------------------------------------------------ {{{2
cpu_info : $(OBJS_CPU_INFO)
	$(CC) $(CFLAGS) $^ -o $(TARGETS_DIR)/$@ $(EXTRAFLAGS)

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# --------------------------------------------------------- 2}}}

# cpu_stress_threads -------------------------------------- {{{2
cpu_stress_threads : $(OBJS_CPU_STRESS_THREADS)
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
