AS = nasm
CC = gcc
LD = ld
ISOGEN = genisoimage

ASFLAGS = -f elf32
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T link.ld -m elf_i386

SRC_C := $(wildcard Bootloading/C\ source\ code/*.c \
                     Input\ Output/C\ source\ code/*.c \
                     Interrupts/C\ source\ code/*.c \
                     Memory\ management/C\ source\ code/*.c \
                     Main\ kernel\ code/C\ source\ code/*.c)

SRC_ASM := $(wildcard Bootloading/Assembly\ source\ code/*.asm \
                        Input\ Output/Assembly\ source\ code/*.asm \
                        Interrupts/Assembly\ source\ code/*.asm \
                        Memory\ management/Assembly\ source\ code/*.asm)

OBJECTS := $(patsubst %.c,%.o,$(SRC_C)) $(patsubst %.asm,%.o,$(SRC_ASM))
OBJECTS := $(subst C source code,Object files,$(OBJECTS))
OBJECTS := $(subst Assembly source code,Object files,$(OBJECTS))

ISO_DIR = Main\ kernel\ code/iso
ISO_NAME = os.iso

all: $(ISO_NAME)

%/Object\ files/%.o: %/C\ source\ code/%.c
	$(CC) $(CFLAGS) -o $@ $<

%/Object\ files/%.o: %/Assembly\ source\ code/%.asm
	$(AS) $(ASFLAGS) -o $@ $<

$(ISO_DIR)/boot/kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

$(ISO_NAME): $(ISO_DIR)/boot/kernel.elf
	$(ISOGEN) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o $(ISO_NAME) $(ISO_DIR)

clean:
	rm -f $(OBJECTS) $(ISO_DIR)/boot/kernel.elf $(ISO_NAME)
