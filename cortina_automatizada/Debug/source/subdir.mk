################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/cortina_automatizada.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/cortina_automatizada.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/cortina_automatizada.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/drivers" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/CMSIS" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/board" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/utilities" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/board" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/API/Inc" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/source" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/drivers" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/CMSIS" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/utilities" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/cortina_automatizada.d ./source/cortina_automatizada.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

