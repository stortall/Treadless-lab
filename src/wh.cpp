#include "socketcan_cpp.h"
#include "vCAN_Writer.hpp"


class WriterHandler {
    
    private:
        int value[8] {0,0,0,0,0,0,0,0};   
        int toEmuFromInput = 123;
        int toICFromInput = 333;
        int toICFromEmu = 321;
    public:
    
    void SetThrottle(int _value) {
        value[0] = _value;
        value[1] = 0;    
        WriteToCAN(toEmuFromInput, value);
    }
    void SetGear(int _value){
        value[2] = _value;
        WriteToCAN(toEmuFromInput, value);
    }
    void ToggleBreak(){
        if(value[1]==0){
           value[1]=1;
           value[0]=0;//turn off throttle
           WriteToCAN(toEmuFromInput, value);  
        }else if(value[1]==1){
            value[1]=0;
            WriteToCAN(toEmuFromInput,value);
        }
    }
    void WriteRPM(float val){

    }
    void WriteVehicleSpeed(float _value){
        value[0] = _value;
        WriteToCAN(toICFromEmu, value);
    }
};