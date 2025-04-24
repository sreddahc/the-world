SRCS = ./src
OBJS = $(wildcard $(SRCS)/*.c) $(wildcard $(SRCS)/*/*.c) $(wildcard $(SRCS)/*/*/*.c)
CC = gcc
COMPILER_FLAGS = -Wall -Werror
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
OBJ_NAME = the_world.out

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

debug:
	$(CC) -g $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)