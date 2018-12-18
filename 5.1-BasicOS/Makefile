
#------------------------------------------------------------------------------
# Makefile for ARM Versatilepb baseboard (ARM926EJ-S2016)
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      <FILE>.i - Builds <FILE>.i preproessed output file
#      <FILE>.asm - Builds <FILE>.asm assembly output of c-program implementaion files and the final output executable
#      <FILE>.o - Builds <FILE>.o object file executable
#      clean - remove all generated files
#      run   - run the executable using qemu	
#
#
#------------------------------------------------------------------------------
#include sources.mk


# Architectures Specific Flags
LINKER_FILE = ARM926EJ.ld
CPU = arm926ej-s
ARCH = armv5te
#MACHINE = realview-pbx-a9
MACHINE = versatilepb
MEMORY = 128M

ifeq ($(MACHINE), realview-pbx-a9)
	DEFINE = -DR
else
	DEFINE = -DV
endif

TARGET = ts
INCLUDES = -I../includes\
	   -I ../driverlib
OBJS = ts.o\
	main.c\
	clcd.c\
	font.c\
	kernel.c

# Compiler Flags and Defines

#  SRC := $(SOURCES_MSP)
#  INC_DIR := $(foreach d, $(INCLUDES), -I$d)
  CC = arm-none-eabi-gcc
  LD = arm-none-eabi-ld
  OBJD = arm-none-eabi-objdump
  CPY = arm-none-eabi-objcopy
  ASM = arm-none-eabi-as
  LDFLAGS = -T $(LINKER_FILE)
  CFLAGS = -mcpu=$(CPU) -march=$(ARCH) -Wall -Werror -O0 -std=c99 -nostdlib $(INCLUDES) $(DEFINE)
  SZ = arm-none-eabi-size

%.o : %.bmp
	$(CPY) -I binary -O elf32-littlearm -B arm $< $@

%.i : %.c
	$(CC) $(CFLAGS) $< -o $@ 

%.s : %.c
	$(CC) $(CFLAGS) -S $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o : %.s
	$(ASM) -o $@ $<

%.elf : %.o
	$(LD) $(LDFLAGS) -o $@ $<

%.bin : %.elf
	$(CPY) -O binary $< $@

$(TARGET).asm : $(TARGET).out
	$(OBJD) -d $< > $@

	
.PHONY : build
build : $(TARGET).bin

.PHONY : run
run : 
	qemu-system-arm -M $(MACHINE) -m $(MEMORY) -kernel $(TARGET).bin -serial mon:stdio
 
	
$(TARGET).elf : $(TARGET).o
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(TARGET).elf
	$(SZ) $(TARGET).elf

$(TARGET).bin : $(TARGET).elf
	$(CPY) -O binary $< $@
	

.PHONY : clean
clean:
	rm -f *.out *.i *.asm *.o *.d *.map *.bin *.elf
