# software version
SW_VER = 1.0.0

# hardware version
HW_VER = 1.0

# output name
TARGET = tuner

# linker script
LD_SCRIPT = stm32l476rgt6.ld

# sources
SRC += main.c startup.c

# util
SRC += ./util/src/stdio.c ./util/src/string.c

# sys
SRC += ./sys/src/critical.c ./sys/src/sem.c
SRC += ./sys/src/ev.c

# devices
SRC += ./dev/src/watchdog.c ./dev/src/debug.c 
SRC += ./dev/src/cpuclock.c ./dev/src/usart1.c 
SRC += ./dev/src/power.c ./dev/src/extimux.c 
SRC += ./dev/src/systime.c ./dev/src/spisw.c
SRC += ./dev/src/lc72131.c ./dev/src/buttons.c
SRC += ./dev/src/bu1924.c

# rds decodes
SRC += ./rds/src/rds.c

# compiler flags
CC_FLAGS  = -mcpu=cortex-m4 -mthumb -g -Os -I. -fdata-sections 
CC_FLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CC_FLAGS += -ffunction-sections -Wl,--gc-sections 
CC_FLAGS += -Wall -Wmissing-field-initializers -Wsign-compare
CC_FLAGS += -Wmissing-parameter-type -Wold-style-declaration
CC_FLAGS += -Woverride-init -Wtype-limits -Wuninitialized
CC_FLAGS += -Wcast-align -Wno-format
CC_FLAGS += -pedantic-errors -std=c99
# version information
CC_FLAGS += -DSW_VER=\"$(SW_VER)\" -DHW_VER=\"$(HW_VER)\" 
 
# linker flags 
LD_FLAGS  = -T$(LD_SCRIPT)
LD_FLAGS += -nostartfiles -Wl,-Map=$(OUTPUT).map,--cref

# object copy flags 
OBC_FLAGS = -O binary

# tools
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBC = arm-none-eabi-objcopy
OBD = arm-none-eabi-objdump
NM = arm-none-eabi-nm
RM = rm
SIZE = arm-none-eabi-size
ECHO = echo

# sources converted to objs
OBJ = $(SRC:%.c=%.o)
# binary file name
OUTPUT = $(TARGET)_$(SW_VER)

# generate elf and bin
all: $(TARGET).elf $(OUTPUT).bin $(TARGET).lst map size

# generate elf file from objs
$(TARGET).elf: $(OBJ)
	@ $(ECHO) ---------------------    Linking   ---------------------
	$(CC) $(CC_FLAGS) $(OBJ) --output $@ $(LD_FLAGS) 

# generate bin file and generate checksum for it 
$(OUTPUT).bin: $(TARGET).elf
	@ $(ECHO) ---------------------    Copying   ---------------------
	$(OBC) $(OBC_FLAGS) $< $@

# geneate listing
$(TARGET).lst: $(TARGET).elf
	@ $(ECHO) ---------------------    Listing   ---------------------
	$(OBD) -S $< > $@

# compile all sources
%.o : %.c
	@ $(ECHO) --------------------- Compiling $< ---------------------
	$(CC) -c $(CC_FLAGS) $< -o $@

# show size information
size: $(TARGET).elf
	@ $(ECHO) --------------------- Section size ---------------------
	$(SIZE) $(TARGET).elf

# generate symbol map
map: $(TARGET).elf
	@ $(ECHO) --------------------- Symbol map ---------------------
	$(NM) -n -o $(TARGET).elf > $(TARGET).map

# cleanser xD
clean:
	$(RM) -f $(OBJ) $(OUTPUT).bin $(TARGET).lst $(TARGET).elf $(TARGET).map
