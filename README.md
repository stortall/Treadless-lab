# Treadless-lab
Code for c++ bootcamp lab

## For execution 
### Run vcan0.sh from util.
### make a new folder build
### stand on the build folder,give cmake ../
### give make

This create two executable input and emu ,run both in two diffrent terminals

#For build make a new 
Use the following command to comnpile driveline_emulator:
g++ driveline_emulator.cpp -lpthread -lncurses

g++ input.cpp vCAN_Writer.cpp socketcan_cpp.cpp wh.cpp  -lncurses -o inp
g++ driveline_emulator.cpp vCAN_Writer2.cpp  socketcan_cpp.cpp -lpthread -o d4
