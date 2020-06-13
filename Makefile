#--------------------------------------------------------------------------------------------------
# @file    Makefile
# @author  Hotboards Team
# @version V1.1
# @date    26-November-2017
# @brief   Application makefile to build the current project, this makefile
#          applies only for stm32f0 targets
#--------------------------------------------------------------------------------------------------
# Name for your current project
PROJECT = test

#----F0 target to use------------------------------------------------------------------------------
MCU = stm32f072rb

#----library paths (can be relative or absolute)---------------------------------------------------
LL    = ../stm32f0/llf0
HAL   = ../stm32f0/half0
CMSIS = ../stm32f0/cmsisf0
OS    = ../rtos

#----Application files to be compiled--------------------------------------------------------------
OBJ = main.o interrupts.o inits.o

#----Global application symbols, change to -DDEBUG to enable semihosting---------------------------
SYMBOLS  = -DNDEBUG

#----Applications paths to files to be compiled (*.c, *.s)-----------------------------------------
VPATH = .

#----Headers file directories(*.h)-----------------------------------------------------------------
INCLUDES = -I .
INCLUDES += -I configs

#----Stack and Heap values-------------------------------------------------------------------------
HEAP  = 0x00000800
STACK = 0x00000400

#----include libraries makefiles-------------------------------------------------------------------
include $(LL)/ll.mk
include $(HAL)/hal.mk
include $(CMSIS)/cmsis.mk
include $(OS)/rtos.mk


#====Apartir de aqui no modifiques nada a menos que sepas lo que hases. ;)=========================
#----Toolchain ( assembler, compiler, linker, etc.. )----------------------------------------------
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OD = arm-none-eabi-objdump
SZ = arm-none-eabi-size
DB = arm-none-eabi-gdb
OC = arm-none-eabi-objcopy

#----CPU Target------------------------------------------------------------------------------------
CPU  = -mthumb                  # Using the Thumb Instruction Set
CPU += -mcpu=cortex-m0          # The CPU Variant (m0, m0plus ,m3, m4)
CPU += -mlittle-endian          # Endianess implemented
CPU += -mfloat-abi=soft         # Which floating point ABI to use

#----Compiler flags--------------------------------------------------------------------------------
CCFLAGS  = $(CPU)
CCFLAGS += -Os                        # Compile with Size Optimizations (O0, O1, O2, O3, Os)
CCFLAGS += -g3                        # Debugging information level (g1, g2, g3)
CCFLAGS += -ffunction-sections        # Create a separate function section
CCFLAGS += -fdata-sections            # Create a separate data section
CCFLAGS += -fno-builtin               # Don't recognize built-in functions that do not begin with ‘__builtin_’ as prefix
CCFLAGS += -std=c99                   # Comply with C99
CCFLAGS += -Wall                      # Be anal Enable All Warnings
CCFLAGS += -pedantic                  # Be extra anal More ANSI Checks
CCFLAGS += -Wstrict-prototypes        # Warn if a function is declared or defined without specifying the argument types
CCFLAGS += -fsigned-char              # char is treated as signed
CCFLAGS += -fdiagnostics-color=always # color the output
CCFLAGS += -fno-common                # compiler should place uninitialized global variables in the data section
CCFLAGS += -fomit-frame-pointer       # Don't keep the frame pointer in a register for functions that don't need one
CCFLAGS += -fverbose-asm              # Put extra commentary information in the generated assembly code

# Assembler and linker flags-----------------------------------------------------------------------
ASFLAGS = $(CPU)
LDFLAGS = $(CPU) -Wl,--gc-sections --specs=nano.specs -lc -lnosys --specs=nosys.specs --specs=rdimon.specs -lc -lrdimon
LDFLAGS += -Wl,-Map=Output/$(PROJECT).map
LDFLAGS += -Xlinker --defsym=_Min_Heap_Size=$(HEAP)
LDFLAGS += -Xlinker --defsym=_Min_Stack_Size=$(STACK)
OCFLAGS = -Oihex
ODFLAGS = -S

#----Build the project-----------------------------------------------------------------------------
all : $(PROJECT)

# Generate binaries, assembler list and display the program size
$(PROJECT) : $(addprefix Output/,$(PROJECT).elf)
	$(OC) $(OCFLAGS) $< Output/$(PROJECT).hex
	$(OD) $(ODFLAGS) $< > Output/$(PROJECT).lst
	$(SZ) --format=berkeley $<

# Link files and generate elf file
Output/$(PROJECT).elf : $(addprefix Output/obj/,$(OBJ))
	$(LD) $(LDFLAGS) -T$(LINKERFILE) -o $@ $^

# Compile C source files
Output/obj/%.o : %.c
	mkdir -p Output/obj
	$(CC) $(CCFLAGS) $(INCLUDES) $(SYMBOLS) -c -o $@ $^

# Compile ASM files
Output/obj/%.o : %.s
	$(AS) $(ASFLAGS) -o $@ $^

clean :
	rm -r Output

flash :
	openocd -f interface/stlink-v2-1.cfg -f target/stm32f0x.cfg -c "program Output/$(PROJECT).hex verify reset" -c shutdown

open :
	openocd -f interface/stlink-v2-1.cfg -f target/stm32f0x.cfg -c "reset_config srst_only srst_nogate"

debug :
	$(DB) -ex "target remote localhost:3333" -ex "mon arm semihosting enable" Output/$(PROJECT).elf -ex "load" -ex "mon reset halt"
