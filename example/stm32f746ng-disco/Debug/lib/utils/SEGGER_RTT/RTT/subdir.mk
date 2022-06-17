################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/utils/SEGGER_RTT/RTT/SEGGER_RTT.c \
../lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.c 

S_UPPER_SRCS += \
../lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT.o \
./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.o \
./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.o 

S_UPPER_DEPS += \
./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT.d \
./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
lib/utils/SEGGER_RTT/RTT/%.o lib/utils/SEGGER_RTT/RTT/%.su: ../lib/utils/SEGGER_RTT/RTT/%.c lib/utils/SEGGER_RTT/RTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/stm32f746ng-disco/lib/utils/SEGGER_RTT/RTT" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lib/utils/SEGGER_RTT/RTT/%.o: ../lib/utils/SEGGER_RTT/RTT/%.S lib/utils/SEGGER_RTT/RTT/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-lib-2f-utils-2f-SEGGER_RTT-2f-RTT

clean-lib-2f-utils-2f-SEGGER_RTT-2f-RTT:
	-$(RM) ./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT.d ./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT.o ./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT.su ./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.d ./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.o ./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.d ./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.o ./lib/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.su

.PHONY: clean-lib-2f-utils-2f-SEGGER_RTT-2f-RTT

