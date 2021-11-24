//#include <chrono>
#include <thread>
#include <iostream>
#include "your_stuff.h"
#include "can_common.h"
#include <sstream>

namespace CANID
{
    const canid_t TO_IC_FROM_EMU = 0x321;
    const canid_t TO_IC_FROM_INPUT = 0x333;
    const canid_t example =0x123;

    //int toEmuFromInput = 0x123;
}// namespace CANID


void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
    switch (_frame->can_id) {
    case CANID::TO_IC_FROM_EMU: {
            const struct CAN::MSG::_engine *d = reinterpret_cast<const struct CAN::MSG::_engine * >((_frame->data));

        this->InstrumentCluster.setSpeed(_frame->data[0]);
        QString accbrakegear = "Speed: " + QString::number(_frame->data[0],10) + "%\n"
                               "RPM: " + QString::number(_frame->data[1],16) + "\n"
                               "Gear:"   + QString::number(_frame->data[2],16)+ "\n";

         //QString vcan0 = "vcan0: " + QString::number(_frame->data[0],16) + ""
        //                        " " + QString::number(_frame->data[1],16) + "\t"
        //                     //    ""   + QString::number(_frame->data[3],16)+ "\t"
        //                     //    ""   + QString::number(_frame->data[4],16)+ "\t"
        //                     //    ""   + QString::number(_frame->data[5],16)+ "\t"
        //                     //    ""   + QString::number(_frame->data[6],16)+ "\t"
        //                     //    ""   + QString::number(_frame->data[7],16)+ "\t"
        //                        ""   + QString::number(_frame->data[8],16)+ "\t";
        ;
        //QByteArray hex =  QByteArray::fromHex(accbrakegear);
        //QString str2 = QString::fromUtf16((char16_t*)hex.data());
        //QByteArray text = QByteArray::fromHex(_frame->data[0]);
           //this->InstrumentCluster.setTXT(text.data());// returns "Qt is great!"  
        //(ss <<(_frame->data[0])) ;
        // (ss1 <<(_frame->data[1])) ;
        // (ss2 <<(_frame->data[2])) ;
        // std::string accbrakegear = "Speed: " + ss.str() + "%\n"
        //                        "Brake: " +ss1.str() + "%\n"
        //                        "Gear:" +ss2.str()+ "%\n";
        this->InstrumentCluster.setTXT(accbrakegear);
        //this->InstrumentCluster.setTXT(vcan0);

        this->InstrumentCluster.setRPM((_frame->data[1])*25);
        this->InstrumentCluster.setGear(_frame->data[2]);

        // const struct CAN::MSG::Gauges_t::_inner* s =
        //         reinterpret_cast<const struct CAN::MSG::Gauges_t::_inner* >((_frame->data));
        // this->InstrumentCluster.setFuelGauges(s->G_FUEL);
        // this->InstrumentCluster.setTemperatureGauges(s->G_TEMP);
        // this->InstrumentCluster.setOilTemperatureGauges(s->G_OILT);
        break;
    }
    case CANID::TO_IC_FROM_INPUT:{
        struct _icons  p;//= reinterpret_cast<struct _icons * >((_frame->data));
        static bool once = false;

        if (!once) {
            p.hazard = 1;
            once = true;
        } else
            p.hazard = 0;
        // QString pp = "icon1: " + QString::number(p) + "%\n"
        //                        "icon2: " + QString::number(p) + "%\n"
        //                        "icon3:" +QString::number(p)+ "%\n";
        // this->InstrumentCluster.setTXT(pp);
        this->InstrumentCluster.setIcon(&p);

        break;
    }
//    case CANID::example:{
//       // const struct CAN::MSG::_userin *d = reinterpret_cast<const struct CAN::MSG::_userin * >((_frame->data));
//       // this->InstrumentCluster.ignite(d->IGNT);
//    }
       break;

    // case CANID::TO_IC_FROM_INPUT {
    //     const struct CAN::MSG::Gearbx_t::_bits *d = reinterpret_cast<const struct CAN::MSG::Gearbx_t::_bits * >((_frame->data));
    //     //this->InstrumentCluster.setGearPindle_int(d->GEAR_P);
    //     this->InstrumentCluster.setGear(_frame->data[2]);
    // }
    //    break;
    //case CAN::MSG::ENGINE_ID: {
    //     const struct CAN::MSG::_engine *d = reinterpret_cast<const struct CAN::MSG::_engine * >((_frame->data));
    //     //this->InstrumentCluster.ignite(d->RUN);
    //     this->InstrumentCluster.setRPM(d->RPM);
    //     this->InstrumentCluster.setSpeed(d->SPD);

    // }
    //     break;
    default:
        break;
    }

}

/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();

    this->InstrumentCluster.init(_vs);

    this->startTimer(1);
}

bool yourStuff::run() {
    bool ret = true;
    CANOpener::ReadStatus status = CANOpener::ReadStatus::OK;
    canfd_frame frame;
    this->CANReader.read(&frame);
    /*while*/if (status == CANOpener::ReadStatus::OK) {
        this->YouHaveJustRecievedACANFrame(&frame);
    }
    if (status == CANOpener::ReadStatus::ERROR) ret = false;
    else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF) this->Counter++;
    else   this->Counter = 0;
    //if (this->Counter > 200) ret = false;
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run());
    else {
//    emit this->die();
        exit(-1);
    }

}

