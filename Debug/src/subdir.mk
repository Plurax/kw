################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglAppConfiguration.cpp \
../src/mglFontProvider.cpp \
../src/mglLibHandle.cpp \
../src/mglLibraryInfo.cpp \
../src/mglMessage.cpp \
../src/mglSelectionContext.cpp \
../src/mglSystem.cpp \
../src/mglTimer.cpp \
../src/mglXMLValueReader.cpp 

OBJS += \
./src/mglAppConfiguration.o \
./src/mglFontProvider.o \
./src/mglLibHandle.o \
./src/mglLibraryInfo.o \
./src/mglMessage.o \
./src/mglSelectionContext.o \
./src/mglSystem.o \
./src/mglTimer.o \
./src/mglXMLValueReader.o 

CPP_DEPS += \
./src/mglAppConfiguration.d \
./src/mglFontProvider.d \
./src/mglLibHandle.d \
./src/mglLibraryInfo.d \
./src/mglMessage.d \
./src/mglSelectionContext.d \
./src/mglSystem.d \
./src/mglTimer.d \
./src/mglXMLValueReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D"__LIBNAME="\"MGlBase\" -D"__BUILD_DATE="\"ARGH\" -I/usr/include/freetype2 -I/usr/include -I"/home/cromas/git/mgl/workspace/MGL/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


