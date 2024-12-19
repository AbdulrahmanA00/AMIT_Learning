################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/INTERRUPT/EXTI/EXT_INT.c 

OBJS += \
./MCAL/INTERRUPT/EXTI/EXT_INT.o 

C_DEPS += \
./MCAL/INTERRUPT/EXTI/EXT_INT.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/INTERRUPT/EXTI/%.o: ../MCAL/INTERRUPT/EXTI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


