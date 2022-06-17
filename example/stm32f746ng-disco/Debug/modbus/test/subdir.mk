################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/test/mb_test_timer_uart.c 

OBJS += \
./modbus/test/mb_test_timer_uart.o 

C_DEPS += \
./modbus/test/mb_test_timer_uart.d 


# Each subdirectory must supply rules for building sources it contributes
modbus/test/%.o modbus/test/%.su: ../modbus/test/%.c modbus/test/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/source/modbus/utils/SEGGER_RTT/RTT" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modbus-2f-test

clean-modbus-2f-test:
	-$(RM) ./modbus/test/mb_test_timer_uart.d ./modbus/test/mb_test_timer_uart.o ./modbus/test/mb_test_timer_uart.su

.PHONY: clean-modbus-2f-test

