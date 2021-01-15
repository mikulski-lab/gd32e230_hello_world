TARGET = gd32e23x_hello_world

BUILDDIR = build
DEPDIR = .depend/build

BUILD_TOOLS = $(TOOLCHAIN)/build-tools/bin
BUSY_BOX = $(BUILD_TOOLS)/busybox

PATH = $(TOOLCHAIN)/gcc-arm-none-eabi
AS = $(PATH)/bin/arm-none-eabi-as
LD = $(PATH)/bin/arm-none-eabi-ld
CC = $(PATH)/bin/arm-none-eabi-gcc
OC = $(PATH)/bin/arm-none-eabi-objcopy
OD = $(PATH)/bin/arm-none-eabi-objdump
OS = $(PATH)/bin/arm-none-eabi-size
GDB = $(PATH)/bin/arm-none-eabi-gdb

CFLAGS = \
	-MT $@ -MMD -MP -MF $(DEPDIR)/$*.d \
	-O2 -fno-tree-vrp -g \
	-mcpu=cortex-m23 -mthumb \
	-ffunction-sections \
	-fdata-sections \
	$(INCLUDE)

LDSCRIPT = ./ld/gd32.ld

LDFLAGS += \
	-T$(LDSCRIPT) \
	-mcpu=cortex-m23 -mthumb \
	-specs=nano.specs \
	-specs=nosys.specs \
	-Wl,--gc-sections \
	-Wl,-Map=$(MAP)

DEFS += \
	-DGD32E230 \
	-DLOG_LEVEL=2

CMSISSRC += lib/CMSIS/GD/GD32E23x/Source/system_gd32e23x.c

GDSRC += lib/GD32E23x_standard_peripheral/Source/gd32e23x_misc.c
GDSRC += lib/GD32E23x_standard_peripheral/Source/gd32e23x_rcu.c
GDSRC += lib/GD32E23x_standard_peripheral/Source/gd32e23x_gpio.c
GDSRC += lib/GD32E23x_standard_peripheral/Source/gd32e23x_exti.c
GDSRC += lib/GD32E23x_standard_peripheral/Source/gd32e23x_usart.c
GDSRC += lib/GD32E23x_standard_peripheral/Source/gd32e23x_syscfg.c
GDSRC += lib/CMSIS/GD/GD32E23x/Source/startup_gd32e23x.s

SRC += $(CMSISSRC)
SRC += $(GDSRC)
SRC += \
	src/gd32e23x_it.c \
	src/main.c \
	src/systick.c \
	src/led.c \
	src/retarget.c \
	src/uart.c

INCLUDE += -Isrc
INCLUDE += -Ilib/CMSIS/GD/GD32E23x/Include
INCLUDE += -Ilib/CMSIS
INCLUDE += -Ilib/GD32E23x_standard_peripheral/Include
INCLUDE += -I$(TOOLCHAIN)/arm-none-eabi/include
INCLUDE += -I$(TOOLCHAIN)/lib/gcc/arm-none-eabi/9.3.1/include
INCLUDE += -I$(TOOLCHAIN)/lib/gcc/arm-none-eabi/9.3.1/include-fixed

GARBAGE = $(DEPDIR) $(BUILDDIR)
OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SRC))))

ELF = $(BUILDDIR)/$(TARGET).elf
MAP = $(BUILDDIR)/$(TARGET).map

all: $(ELF)

$(ELF): $(OBJECTS) $(LDSCRIPT)
	@echo	
	@echo Linking: $@
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)
		
flash: $(ELF) size
	@echo
	@echo Creating .hex and .bin flash images:
	$(OC) -O ihex $< $(BUILDDIR)/$(TARGET).hex
	$(OC) -O binary $< $(BUILDDIR)/$(TARGET).bin
	
size: $(ELF)
	@echo
	@echo == Object size ==
	@$(OS) --format=berkeley $<
	
$(BUILDDIR)/%.o: %.c
	@echo
	@echo Compiling: $<
	$(BUSY_BOX) mkdir -p $(dir $@)
	$(BUSY_BOX) mkdir -p .depend/$(dir $@)
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

$(BUILDDIR)/%.o: %.s
	@echo
	@echo Assembling: $<
	$(BUSY_BOX) mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	@echo Cleaning:
	$(BUSY_BOX) rm -rf $(GARBAGE)
	
gdb:
	@echo GDB starting...
	$(GDB) $(ELF)

.PHONY: bin elf hex flash clean
include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SOURCES))))