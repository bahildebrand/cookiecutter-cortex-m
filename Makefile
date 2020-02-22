TOOLCHAIN := arm-none-eabi-
CC := $(TOOLCHAIN)gcc
OBJCPY := $(TOOLCHAIN)objcopy
SRC_DIR := src
BUILD_DIR := build

.PHONY: all
all: $(BUILD_DIR) $(BUILD_DIR)/m4_example.bin

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

CFLAGS += -nostdlib \
		  -mcpu=cortex-m4 \
		  -g \
		  -Wall \
		  -Werror

SRC := $(wildcard $(SRC_DIR)/*)
OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))

$(BUILD_DIR)/m4_example.bin: $(BUILD_DIR)/m4_example.elf
	$(OBJCPY) $< $@ -O binary

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/m4_example.elf: $(OBJS)
	$(CC) -o $@ $^ -T link/link.ld $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)