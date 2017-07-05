################################################################################
# Automatically-generated file. Do not edit!
################################################################################
# Possibles: SOOPC, LDOOPC, OOCS, OOC
SMELL = OOC

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk

-include src/$(SMELL)/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ComparacionesEnC

# Tool invocations
ComparacionesEnC: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o "ComparacionesEnC" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) ComparacionesEnC
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
