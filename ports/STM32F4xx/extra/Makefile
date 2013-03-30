#
# Makefile para STM32F4xx
# Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
#
#

CROSS_COMPILE=/opt/arm-2012.03/bin/arm-none-eabi-

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy

# Special variables for Cortex-M4F
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=softfp

# Assembler flags
AFLAGS=-mthumb \
       $(CPU)  \
       $(FPU)  \
       -MD

# Include path
INCLUDEDIR+=-I./include \
        -I./ports/STM32F4xx/inc

# GCC C Flags
CFLAGS := -mthumb			\
		$(CPU)				\
		$(FPU)				\
		-Os					\
		-ffunction-sections	\
		-fdata-sections		\
		-MD					\
		-Wall               \
		-c					\
		$(INCLUDEDIR)

# Linker flags
LDFLAGS := --gc-sections

OBJ+=./ports/STM32F4xx/extra/startup_stm32f4xx.o \
    ./ports/STM32F4xx/extra/system_stm32f4xx.o \
	./main.o

PROJECT := stm32f4xx-example

all: $(OBJ)
	@echo "Done building object files"
	@echo
	@echo "Linking..."
	${LD} $(LDFLAGS) -T stm32f4xx_linker.ld $(OBJ) -o $(PROJECT).elf
	@echo "Done. Generating bin file..."
	${OBJCOPY} -O binary $(PROJECT).elf $(PROJECT).bin
	@echo "Done"

clean:
	@echo "Cleaning object files..."
	$(RM) $(OBJ)
	$(RM) $(shell find . -type f -iname "*.d")
	$(RM) $(PROJECT).elf $(PROJECT).bin
	@echo "Done"

