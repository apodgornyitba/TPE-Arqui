include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_DRIVERS=$(wildcard drivers/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_DRIVERS=$(SOURCES_DRIVERS:.c=.o)

all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_DRIVERS) _loader.o
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.o $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_DRIVERS) -o ../$(MODULE)
	# $(GCC) $(GCCFLAGS) -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) -o ../0000-sampleCodeModule.elf

_loader.o:_loader.c
	$(GCC) $(GCCFLAGS) -c _loader.c

%.o:%.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o:%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o
	# rm -rf *.elf *.bin

.PHONY: all clean print
