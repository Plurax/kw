################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglAppConfiguration.cpp \
../src/mglFontProvider.cpp \
../src/mglLibHandle.cpp \
../src/mglMessage.cpp \
../src/mglSystem.cpp \
../src/mglTimer.cpp 

OBJS += \
./src/mglAppConfiguration.o \
./src/mglFontProvider.o \
./src/mglLibHandle.o \
./src/mglMessage.o \
./src/mglSystem.o \
./src/mglTimer.o 

CPP_DEPS += \
./src/mglAppConfiguration.d \
./src/mglFontProvider.d \
./src/mglLibHandle.d \
./src/mglMessage.d \
./src/mglSystem.d \
./src/mglTimer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -I"/home/cromas/git/mgl/workspace/MGL/include" -I/usr/include/freetype2 -I/usr/include -I/home/cromas/git/mgl/workspace/MGL/MGL/MGL/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


