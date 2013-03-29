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
		-std=c99            \
		-Wall               \
		-pedantic           \
		-c					\
		$(INCLUDEDIR)

# Linker flags
LDFLAGS := --gc-sections

OBJ+=./ports/STM32F4xx/src/digital_io.o \
    ./ports/STM32F4xx/src/uart.o \
    ./ports/STM32F4xx/src/i2c_master.o \
    ./ports/STM32F4xx/src/pwm.o \
    ./ports/STM32F4xx/src/spi_master.o \
    ./ports/STM32F4xx/src/timer.o \
    ./ports/STM32F4xx/extras/startup_stm32f4xx.o \
    ./ports/STM32F4xx/extras/system_stm32f4xx.o

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

