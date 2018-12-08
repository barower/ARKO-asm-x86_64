CC = gcc
CCFLAGS = -Wall -g
OBJS_C = main.c drawgraph.c
OBJ_NAME_C = projekt_c

ASM = nasm
ASMFLAGS = -felf64 -l listing.list
OBJS_ASM = main.c drawgraph.o
OBJ_NAME_ASM = projekt_asm

LINKER_FLAGS =  -L/usr/lib/x86_64-linux-gnu -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2_ttf -lm -D_REENTRANT -I/usr/include/SDL2


c: $(OBJS_C)
		$(CC) $(OBJS_C) $(CCFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME_C)

asm: $(OBJS_ASM)
		$(CC) $(OBJS_ASM) $(CCFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME_ASM)

drawgraph.o: drawgraph.s
		$(ASM) $(ASMFLAGS) drawgraph.s

clean:
		rm -f *.o $(OBJ_NAME_ASM) $(OBJ_NAME_C) listing.list
