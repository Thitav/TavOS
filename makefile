CC = i386-elf-gcc
LD = i386-elf-ld
ASMC = nasm

CFLAGS = -ffreestanding -m32 -g -c
ASMFLAGS = -f elf
LDFLAGS = -m elf_i386 -Ttext 0x1000 --oformat binary

CLIB = $(wildcard src/lib/*.c)  $(wildcard src/lib/**/*.c) 
ALIB = $(wildcard src/lib/*.asm) $(wildcard src/lib/**/*.asm)
OBJS = $(CLIB:.c=.o) $(ALIB:.asm=.o)

.PHONY: all clean
all: dirs kernel

dirs:
	mkdir -p ./bin

kernel: $(OBJS)
	$(ASMC) src/boot.asm -o bin/boot.bin -f bin
	$(ASMC) src/kernel_entry.asm -o bin/kernel_entry.o $(ASMFLAGS)
	$(CC) src/kernel.c -o bin/kernel.o $(CFLAGS)
	$(LD) bin/kernel_entry.o bin/kernel.o $^ -o bin/full_kernel.bin $(LDFLAGS)
	cat bin/boot.bin bin/full_kernel.bin > bin/os.bin

%.o: %.c
	$(CC) $< -o $@ $(CFLAGS)

%.o: %.asm
	$(ASMC) $< -o $@ $(ASMFLAGS)

clean:
	rm -rf ./bin $(OBJS)
