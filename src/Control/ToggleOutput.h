#ifndef __TOGGLE_OUTPUT__H__
#define __TOGGLE_OUTPUT__H__

#include "../Interfaces/IToggleOutput.h"

namespace Interfaces
{
    class IFanRpmMonitor;
}

namespace Control
{    
    class ToggleOutput : public Interfaces::IToggleOutput
    {
        unsigned long _lastDebounceTime;  // the last time the output pin was toggled
        const unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
        int _inputPin;
        int _outputPin;
        int _lastState;
        int _state;
        int _toggleState;

        public:
        ToggleOutput(int inputPin, int outputPin);

        void Loop(unsigned long time);
    };
}
#endif  //!__TOGGLE_OUTPUT__H__