################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Pololu/OrangutanBuzzer/OrangutanBuzzer.cpp 

OBJS += \
./Pololu/OrangutanBuzzer/OrangutanBuzzer.o 

CPP_DEPS += \
./Pololu/OrangutanBuzzer/OrangutanBuzzer.d 


# Each subdirectory must supply rules for building sources it contributes
Pololu/OrangutanBuzzer/%.o: ../Pololu/OrangutanBuzzer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	avrg++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


