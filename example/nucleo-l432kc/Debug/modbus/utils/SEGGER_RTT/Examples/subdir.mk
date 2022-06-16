################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/utils/SEGGER_RTT/Examples/Main_RTT_InputEchoApp.c \
../modbus/utils/SEGGER_RTT/Examples/Main_RTT_MenuApp.c \
../modbus/utils/SEGGER_RTT/Examples/Main_RTT_PrintfTest.c \
../modbus/utils/SEGGER_RTT/Examples/Main_RTT_SpeedTestApp.c 

OBJS += \
./modbus/utils/SEGGER_RTT/Examples/Main_RTT_InputEchoApp.o \
./modbus/utils/SEGGER_RTT/Examples/Main_RTT_MenuApp.o \
./modbus/utils/SEGGER_RTT/Examples/Main_RTT_PrintfTest.o \
./modbus/utils/SEGGER_RTT/Examples/Main_RTT_SpeedTestApp.o 

C_DEPS += \
./modbus/utils/SEGGER_RTT/Examples/Main_RTT_InputEchoApp.d \
./modbus/utils/SEGGER_RTT/Examples/Main_RTT_MenuApp.d \
./modbus/utils/SEGGER_RTT/Examples/Main_RTT_PrintfTest.d \
./modbus/utils/SEGGER_RTT/Examples/Main_RTT_SpeedTestApp.d 


# Each subdirectory must supply rules for building sources it contributes
modbus/utils/SEGGER_RTT/Examples/%.o modbus/utils/SEGGER_RTT/Examples/%.su: ../modbus/utils/SEGGER_RTT/Examples/%.c modbus/utils/SEGGER_RTT/Examples/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/modbus/utils/SEGGER_RTT/RTT" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modbus-2f-utils-2f-SEGGER_RTT-2f-Examples

clean-modbus-2f-utils-2f-SEGGER_RTT-2f-Examples:
	-$(RM) ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_InputEchoApp.d ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_InputEchoApp.o ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_InputEchoApp.su ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_MenuApp.d ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_MenuApp.o ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_MenuApp.su ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_PrintfTest.d ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_PrintfTest.o ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_PrintfTest.su ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_SpeedTestApp.d ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_SpeedTestApp.o ./modbus/utils/SEGGER_RTT/Examples/Main_RTT_SpeedTestApp.su

.PHONY: clean-modbus-2f-utils-2f-SEGGER_RTT-2f-Examples

