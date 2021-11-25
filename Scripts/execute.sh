#!/bin/bash

if [ "$1" == "rebuild" ]
then
 rm -r build
 mkdir build
 cd build
 cmake ..
 cd ..
 fi
 vcanUp=$(ip link show | grep -c "vcan0: <NOARP,UP")

if [ $vcanUp -eq 0 ]; 
then 
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
fi
# if [ "$1" == "can" ]
# gnome-terminal --window --geometry 50x50+0+0 --title=CAN_001 -- candump vcan0,001:FFFFFFFF
# gnome-terminal --window --geometry 50x50+10000+0 --title=CAN_002 -- candump vcan0,002:FFFFFFFF
# fi
cd build
make
gnome-terminal --title=emu --geometry 100x5+500+1000 -- ./bin/emu
gnome-terminal -- ./bin/avic -c vcan0
gnome-terminal --title=input --geometry 3x3+50+1000 -- ./bin/input



