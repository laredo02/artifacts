
AS=nasm
CC=g++
LD=gcc
AS_FLAGS=-f elf32
CC_FLAGS=-m32 -c -ffreestanding -fno-exceptions -fno-rtti
LD_FLAGS=-m32 -nostdlib -nodefaultlibs -lgcc

KERNEL_CPP=kernel/kernel.cpp
BOOTSTRAP_ASM=arch/i386/bootstrap.asm

LINKER_SCRIPT=arch/i386/linker.ld

bootstrap.o: $(BOOTSTRAP_ASM)
	mkdir -p ../build/obj
	$(AS) $(AS_FLAGS) $(BOOTSTRAP_ASM) -o ../build/obj/bootstrap.o

kernel.o: $(KERNEL_CPP)
	mkdir -p ../build/obj
	$(CC) $(CC_FLAGS) $(KERNEL_CPP) -o ../build/obj/kernel.o

kernel.bin: bootstrap.o kernel.o
	mkdir -p ../build/bin
	$(LD) ../build/obj/bootstrap.o ../build/obj/kernel.o -T $(LINKER_SCRIPT) $(LD_FLAGS) -o ../build/bin/kernel.bin

kernel: kernel.bin
	echo "Kernel compiled"

iso: kernel.bin
	mkdir -p ../build/iso/boot/grub
	cp ../build/bin/kernel.bin ../build/iso/boot/kernel.bin
	echo "menuentry \"MISO\" {\n\tmultiboot /boot/kernel.bin\n}"  > ../build/iso/boot/grub/grub.cfg
	grub-mkrescue ../build/iso -o ../build/MISO.iso

test: iso
	qemu-system-i386 -cdrom ../build/MISO.iso

clean:
	rm -r ../build

