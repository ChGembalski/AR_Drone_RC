#
# RPi testi2c makefile
#

ARM_CROSS	= arm-linux-gnueabihf-

GC			= $(ARM_CROSS)g++
CC			= $(ARM_CROSS)gcc

########################################
# Flags
########################################
ASMFLAGS	= -S -Wall -O3 
CFLAGS		= -c -Wall -O3 
LDFLAGS		= 

########################################
# Path
########################################
LIB_PATH		= /home/q/DEV/RaspberryPI/RPiLinux/lib
INC_PATH		= /home/q/DEV/RaspberryPI/RPiLinux/usr/include

########################################
# Includes
########################################
CCINCLUDE		= -I $(INC_PATH)
LDINCLUDE		= -I $(LIB_PATH)

########################################
# Source Files
########################################
SRC			= $(shell find ./ -name *.c)

OBJ_C		= $(SRC:%.c=%.o)

ASM_C		= $(SRC:%.c=%.s)

EXEC		= i2c_RPi

########################################
# All
########################################
all: clean $(SRC) $(EXEC)
	echo Done building $(EXEC)

########################################
# Asm
########################################
asm: $(ASM_C)
	echo Done building asm
	
########################################
# Clear
########################################
clean:
	rm -f *.o $(ASM_C) $(EXEC) 
	
########################################
# Exec
########################################
$(EXEC): $(OBJ_C) 
	$(CC) $(LDFLAGS) $(LDINCLUDE) $(OBJ_C) -o $@

########################################
# .c -> .o
########################################
.c.o:
	$(CC) $(CFLAGS) $(CCINCLUDE) $< -o $@

########################################
# .c -> .s
########################################
.c.s:
	$(CC) $(ASMFLAGS) $(CCINCLUDE) $< -o $@

