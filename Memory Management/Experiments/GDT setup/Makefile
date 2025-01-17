AS = nasm
CC = gcc
ISOGEN = genisoimage

ASFLAGS = -f elf32
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T link.ld -m elf_i386

SRC_C = $(wildcard C/*.c)
SRC_ASM = $(wildcard Assembly/*.asm)
OBJECTS = $(patsubst C/%.c,Object/%.o,$(SRC_C)) $(patsubst Assembly/%.asm,Object/%.o,$(SRC_ASM))
ISO_DIR = ./iso
ISO_NAME = os.iso

all: $(ISO_NAME)

Object/%.o: Assembly/%.asm
	$(AS) $(ASFLAGS) -o $@ $<

Object/%.o: C/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(ISO_DIR)/boot/kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@

$(ISO_NAME): $(ISO_DIR)/boot/kernel.elf
	$(ISOGEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $(ISO_NAME) $(ISO_DIR)