#ifndef __IFAN_FAN_MANAGER__H__
#define __IFAN_FAN_MANAGER__H__

namespace Interfaces
{
    class IFanManager
    {
        public:
        virtual void Loop(unsigned long time) = 0;

        virtual int GetFanData() = 0;

        virtual int GetFanDemand() = 0;
    };
}

#endif  //!__IFAN_MANAGER__H__