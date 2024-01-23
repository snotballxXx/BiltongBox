#include <Arduino.h>
#include "./FanRpmMonitor.h"

using namespace Control;

const int PULSE_PER_REV = 2;
const int SAMPLE_RATE = 1000;
volatile int Count = 0;

void ICACHE_RAM_ATTR onPulse()
{
    Count++;
}

FanRpmMonitor::FanRpmMonitor(int feedbackPin) :
    _FeedbackPin(feedbackPin),
    _LastCalculationTime(0),
    _CurrentCount(0)
{     
    pinMode(_FeedbackPin, INPUT);
    attachInterrupt(_FeedbackPin, onPulse, RISING);
}

void FanRpmMonitor::Loop(unsigned long time)
{
    if ((_LastCalculationTime + SAMPLE_RATE) < time)
    {
        _LastCalculationTime = time;
        _CurrentCount = (Count * 60) / 2;
        Count = 0;
    }
}