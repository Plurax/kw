################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglValues/mglValColor.cpp \
../src/mglValues/mglValCoord.cpp \
../src/mglValues/mglValFixedPoint.cpp \
../src/mglValues/mglValInteger.cpp \
../src/mglValues/mglValString.cpp \
../src/mglValues/mglValue.cpp 

OBJS += \
./src/mglValues/mglValColor.o \
./src/mglValues/mglValCoord.o \
./src/mglValues/mglValFixedPoint.o \
./src/mglValues/mglValInteger.o \
./src/mglValues/mglValString.o \
./src/mglValues/mglValue.o 

CPP_DEPS += \
./src/mglValues/mglValColor.d \
./src/mglValues/mglValCoord.d \
./src/mglValues/mglValFixedPoint.d \
./src/mglValues/mglValInteger.d \
./src/mglValues/mglValString.d \
./src/mglValues/mglValue.d 


# Each subdirectory must supply rules for building sources it contributes
src/mglValues/%.o: ../src/mglValues/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D"__LIBNAME="\"MGlBase\" -D"__BUILD_DATE="\"ARGH\" -I/usr/include/freetype2 -I/usr/include -I"/home/cromas/git/mgl/workspace/MGL/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


