################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglCoord.cpp \
../src/mglFontProvider.cpp \
../src/mglGuiActionFactory.cpp \
../src/mglGuiActionFunctor.cpp \
../src/mglGuiLibManager.cpp \
../src/mglGuiObject.cpp \
../src/mglGuiObjectFactory.cpp \
../src/mglInputMessage.cpp \
../src/mglLibHandle.cpp \
../src/mglMessage.cpp \
../src/mglSystem.cpp \
../src/mglTextureManager.cpp \
../src/mglTimer.cpp \
../src/mglValColor.cpp \
../src/mglValFixedPoint.cpp \
../src/mglXMLValueReader.cpp 

OBJS += \
./src/mglCoord.o \
./src/mglFontProvider.o \
./src/mglGuiActionFactory.o \
./src/mglGuiActionFunctor.o \
./src/mglGuiLibManager.o \
./src/mglGuiObject.o \
./src/mglGuiObjectFactory.o \
./src/mglInputMessage.o \
./src/mglLibHandle.o \
./src/mglMessage.o \
./src/mglSystem.o \
./src/mglTextureManager.o \
./src/mglTimer.o \
./src/mglValColor.o \
./src/mglValFixedPoint.o \
./src/mglXMLValueReader.o 

CPP_DEPS += \
./src/mglCoord.d \
./src/mglFontProvider.d \
./src/mglGuiActionFactory.d \
./src/mglGuiActionFunctor.d \
./src/mglGuiLibManager.d \
./src/mglGuiObject.d \
./src/mglGuiObjectFactory.d \
./src/mglInputMessage.d \
./src/mglLibHandle.d \
./src/mglMessage.d \
./src/mglSystem.d \
./src/mglTextureManager.d \
./src/mglTimer.d \
./src/mglValColor.d \
./src/mglValFixedPoint.d \
./src/mglXMLValueReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -I"/home/cromas/git/mgl/workspace/MGL/include/Logger" -I"/home/cromas/git/mgl/workspace/MGL/include" -I/usr/include/freetype2 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


