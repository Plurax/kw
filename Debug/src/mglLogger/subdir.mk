################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglLogger/mglLogChannel.cpp \
../src/mglLogger/mglLogDeviceFile.cpp \
../src/mglLogger/mglLogDeviceStdErr.cpp \
../src/mglLogger/mglLogDeviceStdOut.cpp \
../src/mglLogger/mglLogger.cpp 

OBJS += \
./src/mglLogger/mglLogChannel.o \
./src/mglLogger/mglLogDeviceFile.o \
./src/mglLogger/mglLogDeviceStdErr.o \
./src/mglLogger/mglLogDeviceStdOut.o \
./src/mglLogger/mglLogger.o 

CPP_DEPS += \
./src/mglLogger/mglLogChannel.d \
./src/mglLogger/mglLogDeviceFile.d \
./src/mglLogger/mglLogDeviceStdErr.d \
./src/mglLogger/mglLogDeviceStdOut.d \
./src/mglLogger/mglLogger.d 


# Each subdirectory must supply rules for building sources it contributes
src/mglLogger/%.o: ../src/mglLogger/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -I"/home/cromas/git/mgl/workspace/MGL/include" -I/usr/include/freetype2 -I/usr/include -I/home/cromas/git/mgl/workspace/MGL/MGL/MGL/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


