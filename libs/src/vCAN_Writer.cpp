#include "vCAN_Writer.hpp"

// https://github.com/siposcsaba89/socketcan-cpp




void WriteToCAN(int _id, uint8_t _value[]) {
    scpp::SocketCan sockat_can;
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" <<std::endl;
        exit(-1);
    }

    scpp::CanFrame cf_to_write;
    
    cf_to_write.id =_id;
    cf_to_write.len = 8;
    for (int i = 0; i < 8; ++i) {
        
            cf_to_write.data[i] = _value[i];
        
    } 
    auto write_sc_status = sockat_can.write(cf_to_write);
    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
    else
        printf("Message was written to the socket \n");

}
