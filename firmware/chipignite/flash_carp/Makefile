
TOOLCHAIN_PATH=
# TOOLCHAIN_PATH=/usr/local/bin/
#TOOLCHAIN_PATH=/opt/riscv32imc/bin/
# TOOLCHAIN_PATH=/ef/apps/bin/

# Set the prefix for `riscvXX-unknown-elf-*`
# On installations using `multilib`, this will be `riscv64` even for compiling to 32-bit targets
TOOLCHAIN_PREFIX=riscv32-none-elf
#TOOLCHAIN_PREFIX=riscv32
# ARCH=rv32i
ARCH=rv32i_zicsr

# ---- Test patterns for project raven ----

.SUFFIXES:

# INCLUDES = print.c
PATTERN = flash_carp

hex:  ${PATTERN:=.hex}

%.elf: %.c ../sections.lds ../crt0_vex.S
	#$(TOOLCHAIN_PATH)riscv32-unknown-elf-gcc -O0 -march=rv32i -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -lgcc -o $@ ../start.s ../print_io.c $(INCLUDES) $<
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gcc -I../ -I../generated/ -O0 -mabi=ilp32 -march=$(ARCH) -D__vexriscv__ -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -lgcc -o $@ ../crt0_vex.S ../isr.c ../stub.c  $(INCLUDES)  $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-objdump -D $(PATTERN).elf > $(PATTERN).lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O verilog $< $@
	sed -ie 's/@1000/@0000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O binary $< $@

client: client.c
	gcc client.c -o client

flash: $(PATTERN).hex
	python3 ../util/caravel_hkflash.py $(PATTERN).hex

flash2: $(PATTERN).hex
	python3 ../util/caravel_flash.py $(PATTERN).hex

show_projectid:
	python3 ../util/caravel_projectid.py

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.vvp *.vcd *.hexe *.lst

.PHONY: clean hex all flash

