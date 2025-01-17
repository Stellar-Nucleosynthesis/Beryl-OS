OBJECTS = env_builder.o kernel.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T link.ld -m elf_i386
AS = nasm
ASFLAGS = -f elf32
ISOGEN = genisoimage
ISO_DIR = ./iso
ISO_NAME = os.iso

all: $(ISO_NAME)

env_builder.o: env_builder.asm
	$(AS) $(ASFLAGS) -o $@ $<

kernel.o: kernel.c
	$(CC) $(CFLAGS) -o $@ $<

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@

$(ISO_NAME): kernel.elf
	cp kernel.elf $(ISO_DIR)/boot
	$(ISOGEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $(ISO_NAME) $(ISO_DIR)

clean:
	rm $(OBJECTS) kernel.elf