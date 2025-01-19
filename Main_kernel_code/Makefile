# Compiler and tools
AS = nasm
CC = gcc
LD = ld
ISOGEN = genisoimage

# Flags
ASFLAGS = -f elf32
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T link.ld -m elf_i386

# Directories (relative to Main_kernel_code)
BOOTLOADING_DIR = ../Bootloading
IO_DIR = ../Input_Output
INTERRUPTS_DIR = ../Interrupts
MEMORY_DIR = ../Memory_management
LIB_DIR = ../Libs
KERNEL_DIR = .

ASM_DIR = Assembly_source_code
C_DIR = C_source_code
OBJ_DIR = Object_files
ISO_DIR = iso
ISO_NAME = os.iso

# Source files
ASM_SRC = $(wildcard $(BOOTLOADING_DIR)/$(ASM_DIR)/*.asm \
                    $(IO_DIR)/$(ASM_DIR)/*.asm \
                    $(INTERRUPTS_DIR)/$(ASM_DIR)/*.asm \
                    $(MEMORY_DIR)/$(ASM_DIR)/*.asm \
                    $(KERNEL_DIR)/$(ASM_DIR)/*.asm)
C_SRC = $(wildcard $(BOOTLOADING_DIR)/$(C_DIR)/*.c \
                  $(IO_DIR)/$(C_DIR)/*.c \
                  $(INTERRUPTS_DIR)/$(C_DIR)/*.c \
                  $(MEMORY_DIR)/$(C_DIR)/*.c \
                  $(KERNEL_DIR)/$(C_DIR)/*.c)

CFLAGS += -I$(BOOTLOADING_DIR)/$(C_DIR)
CFLAGS += -I$(IO_DIR)/$(C_DIR)
CFLAGS += -I$(INTERRUPTS_DIR)/$(C_DIR)
CFLAGS += -I$(MEMORY_DIR)/$(C_DIR)
CFLAGS += -I$(KERNEL_DIR)/$(C_DIR)
CFLAGS += -I$(LIB_DIR)

# Object file paths
ASM_OBJ = $(patsubst %.asm,$(KERNEL_DIR)/$(OBJ_DIR)/%.o,$(notdir $(ASM_SRC)))
C_OBJ = $(patsubst %.c,$(KERNEL_DIR)/$(OBJ_DIR)/%.o,$(notdir $(C_SRC)))
ALL_OBJ = $(ASM_OBJ) $(C_OBJ)

# Target: all
all: $(ISO_NAME)

# Compile assembly files
$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(BOOTLOADING_DIR)/$(ASM_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(IO_DIR)/$(ASM_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(INTERRUPTS_DIR)/$(ASM_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(MEMORY_DIR)/$(ASM_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(KERNEL_DIR)/$(ASM_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

# Compile C files
$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(BOOTLOADING_DIR)/$(C_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(IO_DIR)/$(C_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(INTERRUPTS_DIR)/$(C_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(MEMORY_DIR)/$(C_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_DIR)/$(OBJ_DIR)/%.o: $(KERNEL_DIR)/$(C_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Kernel linking
$(ISO_DIR)/boot/kernel.elf: $(ALL_OBJ)
	$(LD) $(LDFLAGS) $(ALL_OBJ) -o $@

# Create ISO
$(ISO_NAME): $(ISO_DIR)/boot/kernel.elf
	$(ISOGEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $@ $(ISO_DIR)
