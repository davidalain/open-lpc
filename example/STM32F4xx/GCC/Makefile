#
# Makefile para STM32F4xx
# Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
#
#

CROSS_COMPILE=/opt/arm-2012.03/bin/arm-none-eabi-

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
NM=$(CROSS_COMPILE)nm

# Special variables for Cortex-M4F
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=softfp

# Assembler flags
AFLAGS=-mthumb \
       $(CPU)  \
       $(FPU)  \
       -MD

# Include path
INCLUDEDIR+=-I../../../include \
        -I../../../ports/STM32F4xx/inc \
		-I./stdlib

# GCC C Flags
CFLAGS := -mthumb			\
		$(CPU)			\
		$(FPU)			\
		-Os			\
		-ffunction-sections	\
		-fdata-sections		\
		-MD			\
		-Wall   		\
		-c			\
		-DHSE_VALUE=8000000	\
		$(INCLUDEDIR)

# Linker flags
LDFLAGS := --gc-sections

OBJ+=./startup_stm32f4xx.o \
    ./system_stm32f4xx.o \
	../../../ports/STM32F4xx/src/misc.o \
	../../../ports/STM32F4xx/src/digital_io.o \
	../../../ports/STM32F4xx/src/uart.o \
	../../../ports/STM32F4xx/src/spi_master.o \
	./main.o \
	./stdlib/serial_io.o

PROJECT := stm32f4xx-example

all: $(OBJ)
	@echo -e "\e[1;32mDone building object files\e[0m"
	@echo
	@echo -e "\e[1;33mLinking...\e[0m"
	${LD} $(LDFLAGS) -T stm32f4xx_linker.ld --entry Reset_Handler $(OBJ) -o $(PROJECT).elf
	@echo "Done. Generating bin file..."
	${OBJCOPY} -O binary $(PROJECT).elf $(PROJECT).bin
	@echo -e "\e[1;32mDone\e[0m"

clean:
	@echo -e "\e[1;33mCleaning object files...\e[0m"
	$(RM) $(OBJ)
	$(RM) $(shell find . -type f -iname "*.d")
	$(RM) $(PROJECT).elf $(PROJECT).bin
	@echo -e "\e[1;32mDone\e[0m"

elf-info:
	$(NM) -SC $(PROJECT).elf

