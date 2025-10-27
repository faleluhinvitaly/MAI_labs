################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Filter.cpp \
../src/MAI.cpp \
../src/PGMreader.cpp 

CPP_DEPS += \
./src/Filter.d \
./src/MAI.d \
./src/PGMreader.d 

OBJS += \
./src/Filter.o \
./src/MAI.o \
./src/PGMreader.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Filter.d ./src/Filter.o ./src/MAI.d ./src/MAI.o ./src/PGMreader.d ./src/PGMreader.o

.PHONY: clean-src

