APP := three_plus_four
CC := gcc
# Use -O0 for easy-to-read assembly; add -g for debugging
CFLAGS := -O0 -g
ASMFLAGS := -S -fverbose-asm -masm=intel

all: $(APP)

$(APP): main.c
	$(CC) $(CFLAGS) -o $@ $<

# Generate assembly from C (Intel syntax) -> main.S
asm: main.c
	$(CC) $(CFLAGS) $(ASMFLAGS) -o main.S $<

# Disassemble the built executable into Intel syntax -> main.disasm.txt
disasm: $(APP)
	objdump -d -M intel $(APP) > main.disasm.txt

run: $(APP)
	./$(APP)

clean:
	rm -f $(APP) main.S main.disasm.txt

.PHONY: all asm disasm run clean
