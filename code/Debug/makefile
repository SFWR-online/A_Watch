################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/csrc/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
lvgl_f103.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
lvgl_f103.list \

OBJCOPY_HEX += \
lvgl_f103.hex \

OBJCOPY_BIN += \
lvgl_f103.bin \


# All Target
all: lvgl_f103.elf secondary-outputs

# Tool invocations
lvgl_f103.elf: $(OBJS) $(USER_OBJS) D:\cubeide\cubework\lvgl_f103\STM32F103RCTX_FLASH.ld
	arm-none-eabi-gcc -o "lvgl_f103.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\cubeide\cubework\lvgl_f103\STM32F103RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="lvgl_f103.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

lvgl_f103.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "lvgl_f103.list"
	@echo 'Finished building: $@'
	@echo ' '

lvgl_f103.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "lvgl_f103.hex"
	@echo 'Finished building: $@'
	@echo ' '

lvgl_f103.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "lvgl_f103.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
