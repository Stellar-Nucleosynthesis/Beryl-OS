This folder is used to experiment with grub bootloader. kernel.asm is loaded as an OS. Linux programs were used for this. To construct an ISO:
1) Source file kernel.asm must be modified
2) kernel.asm is compiled with nasm: >nasm -f elf32 kernel.asm
3) kernel.o is linked, in this case - with ld: >ld -T link.ld -melf_i386 kernel.o -o kernel.elf
Note: 4-KB alignment is not strictly necessary. link.ld can just look like this:
ENTRY(loader)
SECTIONS {
. = 0x00100000;
}
And it works fine. os_noalign.iso is linked with no alignment.
4) Folder structure for the ISO must be generated:
iso
|-- boot
  |-- grub
  | |-- menu.lst
  | |-- stage2_eltorito
  |-- kernel.elf

It is conveniently archived in iso.zip
5) Finally, ISO can be constructed: > genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso 