################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/SmartHome_Interface/SmartHome_Interface.c 

OBJS += \
./APP/SmartHome_Interface/SmartHome_Interface.o 

C_DEPS += \
./APP/SmartHome_Interface/SmartHome_Interface.d 


# Each subdirectory must supply rules for building sources it contributes
APP/SmartHome_Interface/%.o: ../APP/SmartHome_Interface/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


