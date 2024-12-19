################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ServiceLayer/PWM/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TWI/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/INTERRUPT/EXTI/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/Servo/subdir.mk
-include HAL/MCP4018/subdir.mk
-include HAL/LM35/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/EEPROM/subdir.mk
-include HAL/DC_Motor/subdir.mk
-include HAL/Buzzer/subdir.mk
-include HAL/AC/subdir.mk
-include APP/State/subdir.mk
-include APP/SmartHome_Interface/subdir.mk
-include APP/Registeration/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
Smart_Home_Up.lss \

FLASH_IMAGE += \
Smart_Home_Up.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Smart_Home_Up.elf secondary-outputs

# Tool invocations
Smart_Home_Up.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Smart_Home_Up.map -mmcu=atmega32 -o "Smart_Home_Up.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Smart_Home_Up.lss: Smart_Home_Up.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Smart_Home_Up.elf  >"Smart_Home_Up.lss"
	@echo 'Finished building: $@'
	@echo ' '

Smart_Home_Up.hex: Smart_Home_Up.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Smart_Home_Up.elf  "Smart_Home_Up.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Smart_Home_Up.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Smart_Home_Up.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Smart_Home_Up.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
