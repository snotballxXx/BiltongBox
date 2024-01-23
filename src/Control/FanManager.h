#ifndef __FAN_MANAGER__H__
#define __FAN_RPM_MANAGER__H__

#include "../Interfaces/IFanManager.h"

namespace Interfaces
{
    class IFanRpmMonitor;
}

namespace Control
{    
    class FanManager : public Interfaces::IFanManager
    {
        int _speedOutputPin;
        int _speedDemand;
        Interfaces::IFanRpmMonitor* _monitor;

        public:
        FanManager(int speedOutputPin, Interfaces::IFanRpmMonitor* monitor);

        void Loop(unsigned long time);

        int GetFanData();

        int GetFanDemand() { return _speedDemand; }
    };
}
#endif  //!__FAN_MANAGER__H__