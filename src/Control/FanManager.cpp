#include <Arduino.h>
#include "./FanManager.h"
#include "../Interfaces/IFanRpmMonitor.h"

using namespace Control;

FanManager::FanManager(int speedOutputPin, Interfaces::IFanRpmMonitor* monitor) :
    _speedOutputPin(speedOutputPin),
    _speedDemand(0),
    _monitor(monitor)   
{
    pinMode(_speedOutputPin, OUTPUT);

    analogWriteRange(1024);
    analogWriteFreq(25000);
}

void FanManager::Loop(unsigned long time)
{
    _monitor->Loop(time);
    
    delay(20);  
    int demand = analogRead(A0);
    if (demand != _speedDemand)
    {
        _speedDemand = demand;
        analogWrite(_speedOutputPin, _speedDemand);
    }
}

int FanManager::GetFanData()
{
    return _monitor->GetFanRpm();
}