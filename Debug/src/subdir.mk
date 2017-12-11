################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AIPlayer.cpp \
../src/Board.cpp \
../src/Cell.cpp \
../src/Client.cpp \
../src/ConsoleMsgs.cpp \
../src/DefaultLogic.cpp \
../src/Game.cpp \
../src/HumanPlayer.cpp \
../src/MainMenu.cpp \
../src/MiniMaxAlgo.cpp \
../src/Point.cpp \
../src/ReadSettings.cpp \
../src/ServerChecker.cpp \
../src/String.cpp \
../src/main.cpp 

OBJS += \
./src/AIPlayer.o \
./src/Board.o \
./src/Cell.o \
./src/Client.o \
./src/ConsoleMsgs.o \
./src/DefaultLogic.o \
./src/Game.o \
./src/HumanPlayer.o \
./src/MainMenu.o \
./src/MiniMaxAlgo.o \
./src/Point.o \
./src/ReadSettings.o \
./src/ServerChecker.o \
./src/String.o \
./src/main.o 

CPP_DEPS += \
./src/AIPlayer.d \
./src/Board.d \
./src/Cell.d \
./src/Client.d \
./src/ConsoleMsgs.d \
./src/DefaultLogic.d \
./src/Game.d \
./src/HumanPlayer.d \
./src/MainMenu.d \
./src/MiniMaxAlgo.d \
./src/Point.d \
./src/ReadSettings.d \
./src/ServerChecker.d \
./src/String.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


