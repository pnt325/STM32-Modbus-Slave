################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.c \
../modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.c \
../modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.c \
../modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.c 

OBJS += \
./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.o \
./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.o \
./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.o \
./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.o 

C_DEPS += \
./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.d \
./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.d \
./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.d \
./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.d 


# Each subdirectory must supply rules for building sources it contributes
modbus/utils/SEGGER_RTT/Syscalls/%.o modbus/utils/SEGGER_RTT/Syscalls/%.su: ../modbus/utils/SEGGER_RTT/Syscalls/%.c modbus/utils/SEGGER_RTT/Syscalls/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/stm32f746ng-disco/modbus/utils/SEGGER_RTT/RTT" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modbus-2f-utils-2f-SEGGER_RTT-2f-Syscalls

clean-modbus-2f-utils-2f-SEGGER_RTT-2f-Syscalls:
	-$(RM) ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.d ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.o ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.su ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.d ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.o ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.su ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.d ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.o ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.su ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.d ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.o ./modbus/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.su

.PHONY: clean-modbus-2f-utils-2f-SEGGER_RTT-2f-Syscalls

