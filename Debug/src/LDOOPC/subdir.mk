################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LDOOPC/Observer.c \
../src/LDOOPC/SensedValueDisplay.c \
../src/LDOOPC/exception.c \
../src/LDOOPC/ooc.c 

OBJS += \
../src/LDOOPC/Observer.o \
../src/LDOOPC/SensedValueDisplay.o \
../src/LDOOPC/exception.o \
../src/LDOOPC/ooc.o 

C_DEPS += \
../src/LDOOPC/Observer.d \
../src/LDOOPC/SensedValueDisplay.d \
../src/LDOOPC/exception.d \
../src/LDOOPC/ooc.d 


# Each subdirectory must supply rules for building sources it contributes
src/LDOOPC/%.o: ../src/LDOOPC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


