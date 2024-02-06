################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
../dcmotor.c \
../external_eeprom.c \
../gpio.c \
../i2c.c \
../main.c \
../pwm.c \
../seven.segment.c \
../system.c \
../timer1.c \
../uart.c 

OBJS += \
./buzzer.o \
./dcmotor.o \
./external_eeprom.o \
./gpio.o \
./i2c.o \
./main.o \
./pwm.o \
./seven.segment.o \
./system.o \
./timer1.o \
./uart.o 

C_DEPS += \
./buzzer.d \
./dcmotor.d \
./external_eeprom.d \
./gpio.d \
./i2c.d \
./main.d \
./pwm.d \
./seven.segment.d \
./system.d \
./timer1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


