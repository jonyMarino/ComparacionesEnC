################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/OOC/Object.c \
../src/OOC/Observer.c \
../src/OOC/SensedValueDisplay.c 


OBJS += \
./src/OOC/Object.o \
./src/OOC/Observer.o \
./src/OOC/SensedValueDisplay.o 


C_DEPS += \
./src/OOC/Object.d \
./src/OOC/Observer.d \
./src/OOC/SensedValueDisplay.d

	
../src/OOC/%.c: ../src/OOC/%.dc ../src/OOC/%.d
	cd ../src/OOC && ooc -DGNUC=1  $* $*.dc > $*.c
	
../src/OOC/%.h: ../src/OOC/%.d
	cd ../src/OOC && ooc -DGNUC=1  $* -h > $*.h
	
../src/OOC/%.r: ../src/OOC/%.d
	cd ../src/OOC && ooc -DGNUC=1  $* -r > $*.r
	
../src/OOC/Object.c: ../src/OOC/Object.dc ../src/OOC/Object.d
	cd ../src/OOC && ooc -DGNUC=1 -R  Object Object.dc > Object.c
	
../src/OOC/Object.h: ../src/OOC/Object.d
	cd ../src/OOC && ooc -DGNUC=1 -R  Object -h > Object.h
	
../src/OOC/Object.r: ../src/OOC/Object.d
	cd ../src/OOC && ooc -DGNUC=1 -R Object -r > Object.r
	
# Each subdirectory must supply rules for building sources it contributes
src/OOC/%.o: ../src/OOC/%.c ../src/OOC/%.h ../src/OOC/%.r ../src/OOC/Object.h ../src/OOC/Object.r
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '




