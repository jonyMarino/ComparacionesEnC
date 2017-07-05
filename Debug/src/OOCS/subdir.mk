################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/OOCS/object.c \
../src/OOCS/autorelease.c \
../src/OOCS/clonable.c \
../src/OOCS/SensedValueDisplay.c \
../src/OOCS/Observer.c 

OBJS += \
./src/OOCS/object.o \
./src/OOCS/autorelease.o \
./src/OOCS/clonable.o \
./src/OOCS/SensedValueDisplay.o \
./src/OOCS/Observer.o 

C_DEPS += \
./src/OOCS/object.d \
./src/OOCS/autorelease.d \
./src/OOCS/clonable.d \
./src/OOCS/SensedValueDisplay.d \
./src/OOCS/Observer.d


# Each subdirectory must supply rules for building sources it contributes
src/OOCS/%.o: ../src/OOCS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


