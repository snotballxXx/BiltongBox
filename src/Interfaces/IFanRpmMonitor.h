#ifndef __IFAN_RPM_MONITOR__H__
#define __IFAN_RPM_MONITOR__H__

namespace Interfaces
{
    class IFanRpmMonitor
    {
        public:
        virtual void Loop(unsigned long time) = 0;
        virtual int GetFanRpm() = 0;
    };
}

#endif  //!__IFAN_RPM_MONITOR__H__