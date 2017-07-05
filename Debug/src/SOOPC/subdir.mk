################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SOOPC/Observer.c \
../src/SOOPC/SOOPC.c \
../src/SOOPC/SensedValueDisplay.c 

OBJS += \
./src/SOOPC/Observer.o \
./src/SOOPC/SOOPC.o \
./src/SOOPC/SensedValueDisplay.o 

C_DEPS += \
./src/SOOPC/Observer.d \
./src/SOOPC/SOOPC.d \
./src/SOOPC/SensedValueDisplay.d 


# Each subdirectory must supply rules for building sources it contributes
src/SOOPC/%.o: ../src/SOOPC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


