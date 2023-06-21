################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/basicmenu.c \
../Core/Src/flash.c \
../Core/Src/lcd.c \
../Core/Src/listmenu.c \
../Core/Src/lock.c \
../Core/Src/main.c \
../Core/Src/password.c \
../Core/Src/rc522.c \
../Core/Src/selectmunu.c \
../Core/Src/state.c \
../Core/Src/stateCardID.c \
../Core/Src/stateFaceID.c \
../Core/Src/stateMenu.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/subcardid.c \
../Core/Src/subgpio.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/basicmenu.o \
./Core/Src/flash.o \
./Core/Src/lcd.o \
./Core/Src/listmenu.o \
./Core/Src/lock.o \
./Core/Src/main.o \
./Core/Src/password.o \
./Core/Src/rc522.o \
./Core/Src/selectmunu.o \
./Core/Src/state.o \
./Core/Src/stateCardID.o \
./Core/Src/stateFaceID.o \
./Core/Src/stateMenu.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/subcardid.o \
./Core/Src/subgpio.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/basicmenu.d \
./Core/Src/flash.d \
./Core/Src/lcd.d \
./Core/Src/listmenu.d \
./Core/Src/lock.d \
./Core/Src/main.d \
./Core/Src/password.d \
./Core/Src/rc522.d \
./Core/Src/selectmunu.d \
./Core/Src/state.d \
./Core/Src/stateCardID.d \
./Core/Src/stateFaceID.d \
./Core/Src/stateMenu.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/subcardid.d \
./Core/Src/subgpio.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/basicmenu.d ./Core/Src/basicmenu.o ./Core/Src/basicmenu.su ./Core/Src/flash.d ./Core/Src/flash.o ./Core/Src/flash.su ./Core/Src/lcd.d ./Core/Src/lcd.o ./Core/Src/lcd.su ./Core/Src/listmenu.d ./Core/Src/listmenu.o ./Core/Src/listmenu.su ./Core/Src/lock.d ./Core/Src/lock.o ./Core/Src/lock.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/password.d ./Core/Src/password.o ./Core/Src/password.su ./Core/Src/rc522.d ./Core/Src/rc522.o ./Core/Src/rc522.su ./Core/Src/selectmunu.d ./Core/Src/selectmunu.o ./Core/Src/selectmunu.su ./Core/Src/state.d ./Core/Src/state.o ./Core/Src/state.su ./Core/Src/stateCardID.d ./Core/Src/stateCardID.o ./Core/Src/stateCardID.su ./Core/Src/stateFaceID.d ./Core/Src/stateFaceID.o ./Core/Src/stateFaceID.su ./Core/Src/stateMenu.d ./Core/Src/stateMenu.o ./Core/Src/stateMenu.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/subcardid.d ./Core/Src/subcardid.o ./Core/Src/subcardid.su ./Core/Src/subgpio.d ./Core/Src/subgpio.o ./Core/Src/subgpio.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

