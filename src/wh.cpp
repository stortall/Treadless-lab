#include "socketcan_cpp.h"
#include "vCAN_Writer.hpp"


class WriterHandler {
    public:
    void SetThottle(int _value) {
        WriteToCAN(0, _value);
    }
    void SetGear(int _value){
        WriteToCAN(1, _value);
    }
};