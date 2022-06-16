################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT.c \
../modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.c 

S_UPPER_SRCS += \
../modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT.o \
./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.o \
./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.o 

S_UPPER_DEPS += \
./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT.d \
./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
modbus/utils/SEGGER_RTT/RTT/%.o modbus/utils/SEGGER_RTT/RTT/%.su: ../modbus/utils/SEGGER_RTT/RTT/%.c modbus/utils/SEGGER_RTT/RTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I"C:/Users/phatn/Documents/git_repo/stm32_mb_slave/example/nucleo-l432kc/modbus/utils/SEGGER_RTT/RTT" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
modbus/utils/SEGGER_RTT/RTT/%.o: ../modbus/utils/SEGGER_RTT/RTT/%.S modbus/utils/SEGGER_RTT/RTT/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-modbus-2f-utils-2f-SEGGER_RTT-2f-RTT

clean-modbus-2f-utils-2f-SEGGER_RTT-2f-RTT:
	-$(RM) ./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT.d ./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT.o ./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT.su ./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.d ./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.o ./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.d ./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.o ./modbus/utils/SEGGER_RTT/RTT/SEGGER_RTT_printf.su

.PHONY: clean-modbus-2f-utils-2f-SEGGER_RTT-2f-RTT

