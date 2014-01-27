################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglDataLayer/mglShm.cpp 

OBJS += \
./src/mglDataLayer/mglShm.o 

CPP_DEPS += \
./src/mglDataLayer/mglShm.d 


# Each subdirectory must supply rules for building sources it contributes
src/mglDataLayer/%.o: ../src/mglDataLayer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -I"/home/cromas/git/mgl/workspace/MGL/include" -I/usr/include/freetype2 -I/usr/include -I/home/cromas/git/mgl/workspace/MGL/MGL/MGL/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


