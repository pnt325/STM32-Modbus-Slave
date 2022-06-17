################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.c \
../lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.c \
../lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.c \
../lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.c 

OBJS += \
./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.o \
./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.o \
./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.o \
./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.o 

C_DEPS += \
./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.d \
./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.d \
./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.d \
./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.d 


# Each subdirectory must supply rules for building sources it contributes
lib/utils/SEGGER_RTT/Syscalls/%.o lib/utils/SEGGER_RTT/Syscalls/%.su: ../lib/utils/SEGGER_RTT/Syscalls/%.c lib/utils/SEGGER_RTT/Syscalls/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/stm32f746ng-disco/lib/utils/SEGGER_RTT/RTT" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-utils-2f-SEGGER_RTT-2f-Syscalls

clean-lib-2f-utils-2f-SEGGER_RTT-2f-Syscalls:
	-$(RM) ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.d ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.o ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.su ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.d ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.o ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.su ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.d ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.o ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.su ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.d ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.o ./lib/utils/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.su

.PHONY: clean-lib-2f-utils-2f-SEGGER_RTT-2f-Syscalls

