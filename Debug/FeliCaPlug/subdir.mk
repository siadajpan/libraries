################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FeliCaPlug/FeliCaPlug.cpp 

OBJS += \
./FeliCaPlug/FeliCaPlug.o 

CPP_DEPS += \
./FeliCaPlug/FeliCaPlug.d 


# Each subdirectory must supply rules for building sources it contributes
FeliCaPlug/%.o: ../FeliCaPlug/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	avrg++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


