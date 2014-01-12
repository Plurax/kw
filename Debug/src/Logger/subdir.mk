################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Logger/mglLogChannel.cpp \
../src/Logger/mglLogDeviceFile.cpp \
../src/Logger/mglLogDeviceStdErr.cpp \
../src/Logger/mglLogDeviceStdOut.cpp \
../src/Logger/mglLogger.cpp 

OBJS += \
./src/Logger/mglLogChannel.o \
./src/Logger/mglLogDeviceFile.o \
./src/Logger/mglLogDeviceStdErr.o \
./src/Logger/mglLogDeviceStdOut.o \
./src/Logger/mglLogger.o 

CPP_DEPS += \
./src/Logger/mglLogChannel.d \
./src/Logger/mglLogDeviceFile.d \
./src/Logger/mglLogDeviceStdErr.d \
./src/Logger/mglLogDeviceStdOut.d \
./src/Logger/mglLogger.d 


# Each subdirectory must supply rules for building sources it contributes
src/Logger/%.o: ../src/Logger/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -I"/home/cromas/git/mgl/workspace/MGL/include/Logger" -I"/home/cromas/git/mgl/workspace/MGL/include" -I/usr/include/freetype2 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


