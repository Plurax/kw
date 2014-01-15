################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglValues/mglValColor.cpp \
../src/mglValues/mglValCoord.cpp \
../src/mglValues/mglValFixedPoint.cpp \
../src/mglValues/mglXMLValueReader.cpp 

OBJS += \
./src/mglValues/mglValColor.o \
./src/mglValues/mglValCoord.o \
./src/mglValues/mglValFixedPoint.o \
./src/mglValues/mglXMLValueReader.o 

CPP_DEPS += \
./src/mglValues/mglValColor.d \
./src/mglValues/mglValCoord.d \
./src/mglValues/mglValFixedPoint.d \
./src/mglValues/mglXMLValueReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/mglValues/%.o: ../src/mglValues/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -I"/home/cromas/git/mgl/workspace/MGL/include" -I/usr/include/freetype2 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


