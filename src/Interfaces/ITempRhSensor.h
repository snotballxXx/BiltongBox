#ifndef __ITEMP_RH_SENSOR__H__
#define __ITEMP_RH_SENSOR__H__

namespace Interfaces
{
    class ITempRhSensor
    {
        public:
        virtual void GetData(float& temp, float& rh) = 0;
    };
}

#endif  //!__ITEMP_RH_SENSOR__H__