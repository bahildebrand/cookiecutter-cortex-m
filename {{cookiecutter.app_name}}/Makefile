.SECONDARY:

TOOLCHAIN := arm-none-eabi-
CC := $(TOOLCHAIN)gcc
LD := $(TOOLCHAIN)ld
OBJDMP := $(TOOLCHAIN)objdump
OBJCPY := $(TOOLCHAIN)objcopy
SRC_DIR := src
BUILD_DIR := build

.PHONY: all
all: {{cookiecutter.app_name}}

.PHONY: {{cookiecutter.app_name}}
{{cookiecutter.app_name}}: $(BUILD_DIR)/{{cookiecutter.app_name}}.bin $(BUILD_DIR)/{{cookiecutter.app_name}}.dump.txt

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

INCLUDES += -Iinclude

LDFLAGS += -Map=$(BUILD_DIR)/output.map \
		   --gc-sections \
		   -T link/link.ld

CFLAGS += -nostdlib \
		  -mcpu={{cookiecutter.cpu}} \
		  -ffunction-sections \
		  -fdata-sections \
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

$(BUILD_DIR)/%.dump.txt: $(BUILD_DIR)/%.elf
	$(OBJDMP) -D $^ > $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)