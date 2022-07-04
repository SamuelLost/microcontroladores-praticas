################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/PWM_1_FRDM-KL25Z.c \
../source/PWM_2_FRDM-KL25Z.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/PWM_1_FRDM-KL25Z.o \
./source/PWM_2_FRDM-KL25Z.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/PWM_1_FRDM-KL25Z.d \
./source/PWM_2_FRDM-KL25Z.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/PWM_FRDM-KL25Z/board" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/PWM_FRDM-KL25Z/source" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/PWM_FRDM-KL25Z" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/PWM_FRDM-KL25Z/startup" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/PWM_FRDM-KL25Z/CMSIS" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/PWM_FRDM-KL25Z/drivers" -I"/home/samuel/7 Semestre/Micro/microcontroladores-praticas/PWM_FRDM-KL25Z/utilities" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


