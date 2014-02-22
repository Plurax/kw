################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglGui/mglGuiActionFactory.cpp \
../src/mglGui/mglGuiActionFunctor.cpp \
../src/mglGui/mglGuiActionLibHandle.cpp \
../src/mglGui/mglGuiLibHandle.cpp \
../src/mglGui/mglGuiLibManager.cpp \
../src/mglGui/mglGuiObject.cpp \
../src/mglGui/mglGuiObjectFactory.cpp \
../src/mglGui/mglInputMessage.cpp \
../src/mglGui/mglTextureManager.cpp 

OBJS += \
./src/mglGui/mglGuiActionFactory.o \
./src/mglGui/mglGuiActionFunctor.o \
./src/mglGui/mglGuiActionLibHandle.o \
./src/mglGui/mglGuiLibHandle.o \
./src/mglGui/mglGuiLibManager.o \
./src/mglGui/mglGuiObject.o \
./src/mglGui/mglGuiObjectFactory.o \
./src/mglGui/mglInputMessage.o \
./src/mglGui/mglTextureManager.o 

CPP_DEPS += \
./src/mglGui/mglGuiActionFactory.d \
./src/mglGui/mglGuiActionFunctor.d \
./src/mglGui/mglGuiActionLibHandle.d \
./src/mglGui/mglGuiLibHandle.d \
./src/mglGui/mglGuiLibManager.d \
./src/mglGui/mglGuiObject.d \
./src/mglGui/mglGuiObjectFactory.d \
./src/mglGui/mglInputMessage.d \
./src/mglGui/mglTextureManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/mglGui/%.o: ../src/mglGui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -D"__BUILD_DATE="\"ARGH\" -I"/home/cromas/git/mgl/workspace/MGL/include" -I/usr/include/freetype2 -I/usr/include -I/home/cromas/git/mgl/workspace/MGL/MGL/MGL/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


