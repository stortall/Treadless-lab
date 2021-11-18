#include "can_transmitter_receiver.h"
#include "can_frame.h"
#include <socketcan/socketcan_cpp.h>


class CanTransmitter
{
  public:
    CanTransmitterReceiver can_transmitter;
    void SetThrottle(int _value)
    {
        can_frame_structure.value[0] = _value;
        can_frame_structure.value[1] = 0;
        
        can_transmitter.TransmitToBus(can_frame_structure.toEmuFromInput, can_frame_structure.value);
      

    }

    void SetGear(int _value)
    {
      can_frame_structure.value[2]  = _value;
      can_transmitter.TransmitToBus(can_frame_structure.toEmuFromInput, can_frame_structure.value);

    }

    void Togglebrake()
    {
       if(can_frame_structure.value[1] == 0)
        {
            can_frame_structure.value[1] = 1;
            can_frame_structure.value[0] = 0; //turn off throttle
            can_transmitter.TransmitToBus(can_frame_structure.toEmuFromInput, can_frame_structure.value);  
        }else if(can_frame_structure.value[1] == 1)
            {
                can_frame_structure.value[1] = 0;
                can_transmitter.TransmitToBus(can_frame_structure.toEmuFromInput, can_frame_structure.value);

            }
    }

    void WriteRPM(float val)
    {

    }

    void WriteVehicleSpeed(float _value)
    {
        can_frame_structure.value[0] = _value;
        can_transmitter.TransmitToBus(can_frame_structure.toICFromEmu, can_frame_structure.value);


    }

};

