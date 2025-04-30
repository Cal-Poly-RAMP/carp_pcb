# Set the prefix for `riscvXX-unknown-elf-*`
# On installations using `multilib`, this will be `riscv64` even for compiling to 32-bit targets
TOOLCHAIN_PREFIX=riscv32-none-elf
#TOOLCHAIN_PREFIX=riscv32
# ARCH=rv32i
ARCH=rv32i_zicsr

# ---- Project Configuration ----
SRCDIR = src
INCDIR = include
SOURCES = $(wildcard $(SRCDIR)/*.c)
PROJECT = project

# ---- Test patterns for project raven ----

.SUFFIXES:

hex:  $(PROJECT).hex

$(PROJECT).elf: $(SOURCES) ../sections.lds ../crt0_vex.S
	#$(TOOLCHAIN_PREFIX)-gcc -O0 -march=rv32i -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../start.s ../print_io.c $<
	$(TOOLCHAIN_PREFIX)-gcc -I../ -I../generated/ -I$(INCDIR) -O0 -mabi=ilp32 -march=$(ARCH) -D__vexriscv__ -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../crt0_vex.S ../isr.c ../stub.c $(SOURCES)
	$(TOOLCHAIN_PREFIX)-objdump -D $(PROJECT).elf > $(PROJECT).lst

%.hex: %.elf
	$(TOOLCHAIN_PREFIX)-objcopy -O verilog $< $@
	sed -ie 's/@1000/@0000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PREFIX)-objcopy -O binary $< $@

client: client.c
	gcc client.c -o client

flash: $(PROJECT).hex
	python3 ../util/caravel_hkflash.py $(PROJECT).hex

flash2: $(PROJECT).hex
	python3 ../util/caravel_flash.py $(PROJECT).hex

show_projectid:
	python3 ../util/caravel_projectid.py

# ---- Clean ----

clean:
	rm -f $(PROJECT).elf $(PROJECT).hex $(PROJECT).bin $(PROJECT).lst *.vvp *.vcd

.PHONY: clean hex all flash

