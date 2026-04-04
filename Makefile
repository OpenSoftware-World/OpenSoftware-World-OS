# Tools
AS = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

# Folders
BUILD = build
ISO = iso

# Kernel
KERNEL = $(BUILD)/OpenKernel.bin
ISOFILE = opensoftware_world_os_1.0.iso

# Compile Tools
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -ISystemLib/Std -IDrivers/Vga
LDFLAGS = -m elf_i386 -T link.ld

# Source Files
ASM_SRC = Boot/boot.asm Boot/Mboot_desc/mboot.asm
C_SRC = main.c OpenKernel/Drivers/Vga/vga.c OpenKernel/SystemLib/SysCalls/basic_syscall.c OpenKernel/SystemLib/TimeMng/time.c OpenKernel/Kernel/KernelServices/SystemManagement/sysmng.c OSServices/Shell/shell.c OpenKernel/SystemLib/Std/std.c OpenKernel/Drivers/Keyboard/keyboard.c

# Obj
ASM_OBJ = $(ASM_SRC:%.asm=$(BUILD)/%.o)
C_OBJ = $(C_SRC:%.c=$(BUILD)/%.o)

OBJS = $(ASM_OBJ) $(C_OBJ)

all: $(KERNEL)

# Build Folders
$(BUILD):
	mkdir -p $(BUILD)

# Compile ASM
$(BUILD)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

# Compile C
$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Kernel link
$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(KERNEL)

# ISO Folder Structure
iso: $(KERNEL)
	mkdir -p $(ISO)/boot/grub
	cp $(KERNEL) $(ISO)/boot/
	cp Boot/grub/grub.cfg $(ISO)/boot/grub/
	grub-mkrescue -o $(ISOFILE) $(ISO)

# Run
run: iso
	qemu-system-i386 -cdrom $(ISOFILE)

# Clean
clean:
	rm -rf $(BUILD) $(ISO) $(ISOFILE)