################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../API/Src/api_buzzer.c \
../API/Src/api_motor_passos.c \
../API/Src/api_sensor_chuva.c \
../API/Src/api_sensor_luminosidade.c 

C_DEPS += \
./API/Src/api_buzzer.d \
./API/Src/api_motor_passos.d \
./API/Src/api_sensor_chuva.d \
./API/Src/api_sensor_luminosidade.d 

OBJS += \
./API/Src/api_buzzer.o \
./API/Src/api_motor_passos.o \
./API/Src/api_sensor_chuva.o \
./API/Src/api_sensor_luminosidade.o 


# Each subdirectory must supply rules for building sources it contributes
API/Src/%.o: ../API/Src/%.c API/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/drivers" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/CMSIS" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/board" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/utilities" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/board" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/API/Inc" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/source" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/drivers" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/CMSIS" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/utilities" -I"/home/isaac/Documents/Microcontroladores/Cortex-Mx/cortina_automatizada/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-API-2f-Src

clean-API-2f-Src:
	-$(RM) ./API/Src/api_buzzer.d ./API/Src/api_buzzer.o ./API/Src/api_motor_passos.d ./API/Src/api_motor_passos.o ./API/Src/api_sensor_chuva.d ./API/Src/api_sensor_chuva.o ./API/Src/api_sensor_luminosidade.d ./API/Src/api_sensor_luminosidade.o

.PHONY: clean-API-2f-Src

