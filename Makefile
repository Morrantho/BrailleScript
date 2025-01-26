TARGET := bin/bs
MAIN := src/bs
CFLAGS := -g
LIBS := -lm
# real release:
# CFLAGS := -s -Wall -Wextra -Wno-override-init -Ofast -flto -fwhole-program -std=c2x
ifdef rel # dbg release
	CFLAGS := -g -Ofast -fwhole-program -std=c2x
else
	CFLAGS := -g -std=c2x
endif

.PHONY: $(TARGET).s

$(TARGET): $(TARGET).s
	gcc $(CFLAGS) $(TARGET).s -o $(TARGET) $(LIBS)
	objdump -d -M intel $(TARGET) > $(TARGET)_dump.s

$(TARGET).s:
	gcc -S -masm=intel -fverbose-asm $(CFLAGS) $(MAIN).c -o $(TARGET).s

clean:
	@rm -f bin/*