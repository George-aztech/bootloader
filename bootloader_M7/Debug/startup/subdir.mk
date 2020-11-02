################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mimxrt1021.c 

OBJS += \
./startup/startup_mimxrt1021.o 

C_DEPS += \
./startup/startup_mimxrt1021.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1021DAG5A -DBL_FEATURE_HAS_FLEXSPI_NOR_ROMAPI=1 -DCPU_MIMXRT1021DAG5A_cm7 -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DSKIP_SYSCLK_INIT -DDATA_SECTION_IS_CACHEABLE=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\NXP\workspace\bootloader_M7\board" -I"D:\NXP\workspace\bootloader_M7\source" -I"D:\NXP\workspace\bootloader_M7" -I"D:\NXP\workspace\bootloader_M7\drivers" -I"D:\NXP\workspace\bootloader_M7\device" -I"D:\NXP\workspace\bootloader_M7\CMSIS" -I"D:\NXP\workspace\bootloader_M7\utilities" -I"D:\NXP\workspace\bootloader_M7\component\serial_manager" -I"D:\NXP\workspace\bootloader_M7\component\lists" -I"D:\NXP\workspace\bootloader_M7\component\uart" -I"D:\NXP\workspace\bootloader_M7\xip" -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


