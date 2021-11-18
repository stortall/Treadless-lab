#ifndef CAN_TRANSMITTER_RECEIVER_H
#define CAN_TRANSMITTER_RECEIVER_H
#include <iostream>
#include <socketcan/socketcan_cpp.h>
#include <chrono>
#include <thread>

class CanTransmitterReceiver
{
  public:
    void TransmitToBus(int _id, int _value[]);
    //void ReceiveFromBus();
    scpp::CanFrame can_frame;
    scpp::SocketCan socket_can;

};




#endif // CAN_TRANSMITTER_RECEIVER_H