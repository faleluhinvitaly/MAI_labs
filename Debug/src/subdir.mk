################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DynamicArray.cpp \
../src/DynamicArray_test.cpp \
../src/MAI.cpp 

CPP_DEPS += \
./src/DynamicArray.d \
./src/DynamicArray_test.d \
./src/MAI.d 

OBJS += \
./src/DynamicArray.o \
./src/DynamicArray_test.o \
./src/MAI.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/cyberdemon/eclipse-workspace/MAI/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/DynamicArray.d ./src/DynamicArray.o ./src/DynamicArray_test.d ./src/DynamicArray_test.o ./src/MAI.d ./src/MAI.o

.PHONY: clean-src

