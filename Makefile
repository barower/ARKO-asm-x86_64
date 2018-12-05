OBJS = main.c drawgraph.c

CC = gcc

COMPILER_FLAGS = -Wall -g

LINKER_FLAGS =  -L/usr/lib/x86_64-linux-gnu -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2_ttf -D_REENTRANT -I/usr/include/SDL2

OBJ_NAME = arko_x86_64

all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

