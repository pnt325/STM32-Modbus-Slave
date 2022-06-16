################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/bsp_mb_slave.c \
../modbus/mb_assert.c \
../modbus/mb_buffer.c \
../modbus/mb_crc.c \
../modbus/mb_slave.c \
../modbus/ring_buffer.c 

OBJS += \
./modbus/bsp_mb_slave.o \
./modbus/mb_assert.o \
./modbus/mb_buffer.o \
./modbus/mb_crc.o \
./modbus/mb_slave.o \
./modbus/ring_buffer.o 

C_DEPS += \
./modbus/bsp_mb_slave.d \
./modbus/mb_assert.d \
./modbus/mb_buffer.d \
./modbus/mb_crc.d \
./modbus/mb_slave.d \
./modbus/ring_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
modbus/%.o modbus/%.su: ../modbus/%.c modbus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/nucleo-l432kc/modbus/utils/SEGGER_RTT/RTT" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modbus

clean-modbus:
	-$(RM) ./modbus/bsp_mb_slave.d ./modbus/bsp_mb_slave.o ./modbus/bsp_mb_slave.su ./modbus/mb_assert.d ./modbus/mb_assert.o ./modbus/mb_assert.su ./modbus/mb_buffer.d ./modbus/mb_buffer.o ./modbus/mb_buffer.su ./modbus/mb_crc.d ./modbus/mb_crc.o ./modbus/mb_crc.su ./modbus/mb_slave.d ./modbus/mb_slave.o ./modbus/mb_slave.su ./modbus/ring_buffer.d ./modbus/ring_buffer.o ./modbus/ring_buffer.su

.PHONY: clean-modbus

