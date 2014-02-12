################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglDebug/mglException.cpp \
../src/mglDebug/mglLogChannel.cpp \
../src/mglDebug/mglLogDeviceFile.cpp \
../src/mglDebug/mglLogDeviceStdErr.cpp \
../src/mglDebug/mglLogDeviceStdOut.cpp \
../src/mglDebug/mglLogger.cpp 

OBJS += \
./src/mglDebug/mglException.o \
./src/mglDebug/mglLogChannel.o \
./src/mglDebug/mglLogDeviceFile.o \
./src/mglDebug/mglLogDeviceStdErr.o \
./src/mglDebug/mglLogDeviceStdOut.o \
./src/mglDebug/mglLogger.o 

CPP_DEPS += \
./src/mglDebug/mglException.d \
./src/mglDebug/mglLogChannel.d \
./src/mglDebug/mglLogDeviceFile.d \
./src/mglDebug/mglLogDeviceStdErr.d \
./src/mglDebug/mglLogDeviceStdOut.d \
./src/mglDebug/mglLogger.d 


# Each subdirectory must supply rules for building sources it contributes
src/mglDebug/%.o: ../src/mglDebug/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -I"/home/cromas/git/mgl/workspace/MGL/include" -I/usr/include/freetype2 -I/usr/include -I/home/cromas/git/mgl/workspace/MGL/MGL/MGL/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


