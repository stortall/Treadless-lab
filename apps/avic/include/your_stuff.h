#ifndef YOUR_STUFF_H
#define YOUR_STUFF_H
#include "can_opener.h"
#include "cluster_updater.h"
#include <stdint.h>

class yourStuff : public QObject {
    Q_OBJECT
public:
    yourStuff() = delete;
    yourStuff(const std::string &_ifName, QObject *_);
    void SetIcons(uint8_t data1,uint8_t data2);
     _icons icons;


private:
    bool run();
    void YouHaveJustRecievedACANFrame(const canfd_frame * const _frame);    
    void timerEvent(QTimerEvent*) override;
    //void SetIcons(__u8 data1,__u8 data2);
    double x;


//signals:
//    void die();

private:
    size_t Counter;
    CANOpener CANReader;
    ClusterUpdater InstrumentCluster;
   // _icons icons;

};

#endif // YOUR_STUFF_H
