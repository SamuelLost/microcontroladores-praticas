################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/system/system.c \
../source/system/tasks.c 

OBJS += \
./source/system/system.o \
./source/system/tasks.o 

C_DEPS += \
./source/system/system.d \
./source/system/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
source/system/%.o: ../source/system/%.c source/system/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DCPU_MKL46Z256VLL4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/board" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/source" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/amazon-freertos/FreeRTOS/portable" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/freertos/portable" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/amazon-freertos/include" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/drivers" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/utilities" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/startup" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/Estufa_RTOS_KL46Z/CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


