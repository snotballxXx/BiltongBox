#ifndef __FAN_RPM_MONITOR__H__
#define __FAN_RPM_MONITOR__H__

#include "../Interfaces/IFanRpmMonitor.H"

namespace Control
{    
    class FanRpmMonitor : public Interfaces::IFanRpmMonitor
    {
        int _FeedbackPin;
        int _CurrentCount;
        unsigned long _LastCalculationTime;

        public:
        FanRpmMonitor(int feedbackPin);

        void Loop(unsigned long time);

        int GetFanRpm() { return _CurrentCount; }
    };
}
#endif  //!__FAN_RPM_MONITOR__H__