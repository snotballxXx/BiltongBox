#include "./TempRhSensor.h"
#include "../Constants.h"

#define DHTPIN D1     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

using namespace Control;
   
TempRhSensor::TempRhSensor() :
    _rh(0.0),
    _temp(0.0),
    _lastUpdateTime(0)
{
    _DHT = new DHT(DHTPIN, DHTTYPE);
    _DHT->begin();
}

void TempRhSensor::GetData(float& temp, float& rh)
{
    temp = _temp;
    rh = _rh;
}

void TempRhSensor::Loop(unsigned long time)
{
    if ((_lastUpdateTime + INTERVAL) < time)
    {
        _temp = _DHT->readTemperature();
        _rh = _DHT->readHumidity();

        _lastUpdateTime = time;      
    }
}