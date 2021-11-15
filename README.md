# Treadless-lab
Code for c++ bootcamp lab

##For execution 
1.Run vcan0.sh from util.
2.make a new folder build
3.stand on the build folder,give cmake ../
4.give make

#For build make a new 
Use the following command to comnpile driveline_emulator:
g++ driveline_emulator.cpp -lpthread -lncurses

g++ input.cpp vCAN_Writer.cpp socketcan_cpp.cpp wh.cpp  -lncurses -o inp
g++ driveline_emulator.cpp vCAN_Writer2.cpp  socketcan_cpp.cpp -lpthread -o d4
