################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ServiceLayer/PWM/PWM.c 

OBJS += \
./ServiceLayer/PWM/PWM.o 

C_DEPS += \
./ServiceLayer/PWM/PWM.d 


# Each subdirectory must supply rules for building sources it contributes
ServiceLayer/PWM/%.o: ../ServiceLayer/PWM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


