################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/SMART_HOMRE/LM_WITH_DC_MOTOR.c 

OBJS += \
./APP/SMART_HOMRE/LM_WITH_DC_MOTOR.o 

C_DEPS += \
./APP/SMART_HOMRE/LM_WITH_DC_MOTOR.d 


# Each subdirectory must supply rules for building sources it contributes
APP/SMART_HOMRE/%.o: ../APP/SMART_HOMRE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


