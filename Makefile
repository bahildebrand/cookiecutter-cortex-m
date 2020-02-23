.SECONDARY:

TOOLCHAIN := arm-none-eabi-
CC := $(TOOLCHAIN)gcc
LD := $(TOOLCHAIN)ld
OBJCPY := $(TOOLCHAIN)objcopy
SRC_DIR := src
BUILD_DIR := build

.PHONY: all
all: m4_basic

.PHONY: m4_basic
m4_basic: $(BUILD_DIR)/m4_basic.bin

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

INCLUDES += -Iinclude

LDFLAGS += -Map=$(BUILD_DIR)/output.map \
		   -T link/link.ld

CFLAGS += -nostdlib \
		  -mcpu=cortex-m4 \
		  $(INCLUDES) \
		  -g \
		  -Wall \
		  -Werror

SRC := $(wildcard $(SRC_DIR)/*)
OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCPY) $< $@ -O binary

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.elf: $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)