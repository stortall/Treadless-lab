# Treadless-lab
Code for c++ bootcamp lab


Use the following command to comnpile driveline_emulator:
g++ driveline_emulator.cpp -lpthread -lncurses

g++ input.cpp vCAN_Writer.cpp socketcan_cpp.cpp wh.cpp  -lncurses -o inp
g++ driveline_emulator.cpp vCAN_Writer2.cpp  socketcan_cpp.cpp -lpthread -o d4