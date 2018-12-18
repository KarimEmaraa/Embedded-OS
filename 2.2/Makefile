
#------------------------------------------------------------------------------
# Makefile for ARM Versatilepb baseboard (ARM926EJ-S2016)
#
# 
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

TARGET = ts

# Compiler Flags and Defines

#  SRC := $(SOURCES_MSP)
#  INC_DIR := $(foreach d, $(INCLUDES_MSP), -I$d)
  CC = arm-none-eabi-gcc
  LD = arm-none-eabi-ld
  OBJD = arm-none-eabi-objdump
  CPY = arm-none-eabi-objcopy
  ASM = arm-none-eabi-as
  LDFLAGS = -T $(LINKER_FILE)
  CFLAGS = -mcpu=$(CPU) -march=$(ARCH) -Wall -Werror -g -O0 -std=c99 $(INC_DIR)
  SZ = arm-none-eabi-size


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
build : $(TARGET).out

.PHONY : run
run : $(TARGET)
	qemu-system-arm -M versatilepb -kernel ts.bin -nographic -serial /dev/null

.PHONY : elf
elf :  $(TARGET) 

$(TARGET) : $(TARGET).s
	$(ASM) -o $(TARGET).o $<
	$(LD) $(LDFLAGS) -o $@ $(TARGET).o
	$(CPY) -O binary $@ $(TARGET).bin
	




.PHONY : clean
clean:
	rm -f *.out *.i *.asm *.o *.d *.map *.bin *.elf
