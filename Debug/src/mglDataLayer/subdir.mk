################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mglDataLayer/mglDataContainer.cpp \
../src/mglDataLayer/mglDataLibHandle.cpp \
../src/mglDataLayer/mglDataSource.cpp \
../src/mglDataLayer/mglDataSourceFactory.cpp \
../src/mglDataLayer/mglDataSourceManager.cpp \
../src/mglDataLayer/mglShm.cpp \
../src/mglDataLayer/mglSocket.cpp 

OBJS += \
./src/mglDataLayer/mglDataContainer.o \
./src/mglDataLayer/mglDataLibHandle.o \
./src/mglDataLayer/mglDataSource.o \
./src/mglDataLayer/mglDataSourceFactory.o \
./src/mglDataLayer/mglDataSourceManager.o \
./src/mglDataLayer/mglShm.o \
./src/mglDataLayer/mglSocket.o 

CPP_DEPS += \
./src/mglDataLayer/mglDataContainer.d \
./src/mglDataLayer/mglDataLibHandle.d \
./src/mglDataLayer/mglDataSource.d \
./src/mglDataLayer/mglDataSourceFactory.d \
./src/mglDataLayer/mglDataSourceManager.d \
./src/mglDataLayer/mglShm.d \
./src/mglDataLayer/mglSocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/mglDataLayer/%.o: ../src/mglDataLayer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D"__LIBNAME="\"MGlBase\" -D"__BUILD_DATE="\"ARGH\" -I/usr/include/freetype2 -I/usr/include -I"/home/cromas/git/mgl/workspace/MGL/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


