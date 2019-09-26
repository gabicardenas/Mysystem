################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/HAL/GPIO_Driver.c 

OBJS += \
./source/HAL/GPIO_Driver.o 

C_DEPS += \
./source/HAL/GPIO_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
source/HAL/%.o: ../source/HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL27Z64VLH4 -DCPU_MKL27Z64VLH4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Gabi\Documents\p1_micros\p1_temporizador\source\APP" -I"C:\Users\Gabi\Documents\p1_micros\p1_temporizador\source\HAL" -I"C:\Users\Gabi\Documents\p1_micros\p1_temporizador\source\HIL" -I"C:\Users\Gabi\Documents\p1_micros\p1_temporizador\source\SL" -I../source -I../ -I../device -I../CMSIS -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


