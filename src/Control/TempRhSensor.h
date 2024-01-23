#ifndef __TEMP_RH_SENSOR__H__
#define __TEMP_RH_SENSOR__H__
#include <DHT.h>

#include "../Interfaces/ITempRhSensor.h"

namespace Control
{    
    class TempRhSensor : public Interfaces::ITempRhSensor
    {
        DHT* _DHT;
        unsigned long _lastUpdateTime;
        float _temp;
        float _rh;

        public:
        TempRhSensor();

        void GetData(float& temp, float& rh);
        void Loop(unsigned long time);
    };
}
#endif  //!__TEMP_RH_SENSOR__H__