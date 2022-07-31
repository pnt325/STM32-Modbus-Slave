################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/bsp_mb_slave.c \
../lib/mb_assert.c \
../lib/mb_buffer.c \
../lib/mb_crc.c \
../lib/mb_slave.c \
../lib/ring_buffer.c 

OBJS += \
./lib/bsp_mb_slave.o \
./lib/mb_assert.o \
./lib/mb_buffer.o \
./lib/mb_crc.o \
./lib/mb_slave.o \
./lib/ring_buffer.o 

C_DEPS += \
./lib/bsp_mb_slave.d \
./lib/mb_assert.d \
./lib/mb_buffer.d \
./lib/mb_crc.d \
./lib/mb_slave.d \
./lib/ring_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o lib/%.su: ../lib/%.c lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/nucleo-l432kc/lib/utils/SEGGER_RTT/RTT" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib

clean-lib:
	-$(RM) ./lib/bsp_mb_slave.d ./lib/bsp_mb_slave.o ./lib/bsp_mb_slave.su ./lib/mb_assert.d ./lib/mb_assert.o ./lib/mb_assert.su ./lib/mb_buffer.d ./lib/mb_buffer.o ./lib/mb_buffer.su ./lib/mb_crc.d ./lib/mb_crc.o ./lib/mb_crc.su ./lib/mb_slave.d ./lib/mb_slave.o ./lib/mb_slave.su ./lib/ring_buffer.d ./lib/ring_buffer.o ./lib/ring_buffer.su

.PHONY: clean-lib

