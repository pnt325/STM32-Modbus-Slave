################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/data/mb_data.c \
../lib/data/mb_data_bit.c \
../lib/data/mb_data_reg.c 

OBJS += \
./lib/data/mb_data.o \
./lib/data/mb_data_bit.o \
./lib/data/mb_data_reg.o 

C_DEPS += \
./lib/data/mb_data.d \
./lib/data/mb_data_bit.d \
./lib/data/mb_data_reg.d 


# Each subdirectory must supply rules for building sources it contributes
lib/data/%.o lib/data/%.su: ../lib/data/%.c lib/data/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/stm32f746ng-disco/lib/utils/SEGGER_RTT/RTT" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-data

clean-lib-2f-data:
	-$(RM) ./lib/data/mb_data.d ./lib/data/mb_data.o ./lib/data/mb_data.su ./lib/data/mb_data_bit.d ./lib/data/mb_data_bit.o ./lib/data/mb_data_bit.su ./lib/data/mb_data_reg.d ./lib/data/mb_data_reg.o ./lib/data/mb_data_reg.su

.PHONY: clean-lib-2f-data
