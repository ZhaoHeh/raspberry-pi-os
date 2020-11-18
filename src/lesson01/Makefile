ARMGNU ?= aarch64-linux-gnu

COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
ASMOPS = -Iinclude 

BUILD_DIR = build
SRC_DIR = src

.PHONY: all clean

all : kernel8.img

clean :
	rm -rf $(BUILD_DIR) *.img 

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@
# mkdir -p build
# aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c src/mini_uart.c -o build/mini_uart_c.o
# mkdir -p build
# aarch64-linux-gnu-gcc -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD -c src/kernel.c -o build/kernel_c.o

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@
# aarch64-linux-gnu-gcc -Iinclude  -MMD -c src/utils.S -o build/utils_s.o
# aarch64-linux-gnu-gcc -Iinclude  -MMD -c src/mm.S -o build/mm_s.o
# aarch64-linux-gnu-gcc -Iinclude  -MMD -c src/boot.S -o build/boot_s.o

C_FILES = $(wildcard $(SRC_DIR)/*.c)
# src/mini_uart.c src/kernel.c

ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
# src/utils.S src/mm.S src/boot.S

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
# build/mini_uart_c.o build/kernel_c.o

OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)
# build/mini_uart_c.o build/kernel_c.o build/utils_s.o build/mm_s.o build/boot_s.o

DEP_FILES = $(OBJ_FILES:%.o=%.d)
# build/mini_uart_c.d build/kernel_c.d build/utils_s.d build/mm_s.d build/boot_s.d
# 这5个.d文件是在编译器生成.o文件的时候自动生成的记录依赖信息的文件, 会和.o文件在统一目录

-include $(DEP_FILES)
# 通常我们在Makefile中可使用"-include"来代替"include", 来忽略由于包含文件不存在或者无法创建时的错误提示
# ("-")的意思是告诉make, 忽略此操作的错误, make继续执行
# 像下边那样：
# -include FILENAMES...
# 使用这种方式时, 当所要包含的文件不存在时不会有错误提示, make也不会退出. 除此之外, 和include方式效果相同

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf  $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
# aarch64-linux-gnu-ld -T src/linker.ld -o build/kernel8.elf  build/mini_uart_c.o build/kernel_c.o build/utils_s.o build/mm_s.o build/boot_s.o
# aarch64-linux-gnu-objcopy build/kernel8.elf -O binary kernel8.img
