################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/cpu/nvic.c" \
"../Sources/cpu/sysinit.c" \

C_SRCS += \
../Sources/cpu/nvic.c \
../Sources/cpu/sysinit.c \

OBJS += \
./Sources/cpu/nvic.o \
./Sources/cpu/sysinit.o \

OBJS_QUOTED += \
"./Sources/cpu/nvic.o" \
"./Sources/cpu/sysinit.o" \

C_DEPS += \
./Sources/cpu/nvic.d \
./Sources/cpu/sysinit.d \

OBJS_OS_FORMAT += \
./Sources/cpu/nvic.o \
./Sources/cpu/sysinit.o \

C_DEPS_QUOTED += \
"./Sources/cpu/nvic.d" \
"./Sources/cpu/sysinit.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/cpu/nvic.o: ../Sources/cpu/nvic.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/cpu/nvic.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/cpu/nvic.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/cpu/sysinit.o: ../Sources/cpu/sysinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/cpu/sysinit.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/cpu/sysinit.o"
	@echo 'Finished building: $<'
	@echo ' '


