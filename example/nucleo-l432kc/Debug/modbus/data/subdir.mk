################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/data/mb_data.c \
../modbus/data/mb_data_bit.c \
../modbus/data/mb_data_reg.c 

OBJS += \
./modbus/data/mb_data.o \
./modbus/data/mb_data_bit.o \
./modbus/data/mb_data_reg.o 

C_DEPS += \
./modbus/data/mb_data.d \
./modbus/data/mb_data_bit.d \
./modbus/data/mb_data_reg.d 


# Each subdirectory must supply rules for building sources it contributes
modbus/data/%.o modbus/data/%.su: ../modbus/data/%.c modbus/data/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/nucleo-l432kc/modbus/utils/SEGGER_RTT/RTT" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modbus-2f-data

clean-modbus-2f-data:
	-$(RM) ./modbus/data/mb_data.d ./modbus/data/mb_data.o ./modbus/data/mb_data.su ./modbus/data/mb_data_bit.d ./modbus/data/mb_data_bit.o ./modbus/data/mb_data_bit.su ./modbus/data/mb_data_reg.d ./modbus/data/mb_data_reg.o ./modbus/data/mb_data_reg.su

.PHONY: clean-modbus-2f-data

