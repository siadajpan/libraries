################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Pololu/PololuWheelEncoders/PololuWheelEncoders.cpp 

OBJS += \
./Pololu/PololuWheelEncoders/PololuWheelEncoders.o 

CPP_DEPS += \
./Pololu/PololuWheelEncoders/PololuWheelEncoders.d 


# Each subdirectory must supply rules for building sources it contributes
Pololu/PololuWheelEncoders/%.o: ../Pololu/PololuWheelEncoders/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	avrg++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


