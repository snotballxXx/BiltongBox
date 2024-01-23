#include <Arduino.h>
#include "./ToggleOutput.h"

using namespace Control;

ToggleOutput::ToggleOutput(int inputPin, int outputPin) :
    _inputPin(inputPin),
    _outputPin(outputPin),
    _state(0),
    _lastDebounceTime(0),
    _toggleState(0)

{
    pinMode(_inputPin, INPUT);
    pinMode(_outputPin, OUTPUT);
    digitalWrite(_outputPin, 1);

    _state = digitalRead(_inputPin);
}

void ToggleOutput::Loop(unsigned long time)
{
    int state = digitalRead(_inputPin);

    if (_lastState != state)
    {
        Serial.println("State change pending...");
        _lastDebounceTime = time;
    }

    if ((time - _lastDebounceTime) > debounceDelay) 
    {
        if (_state != state) 
        {        
            Serial.print("State change ");
            Serial.println(state);
            _state = state;

            if (_state == HIGH)
            {
                _toggleState = _toggleState == HIGH ? LOW : HIGH;
                Serial.print("Switching state ");
                Serial.println(_toggleState);
                digitalWrite(_outputPin, _toggleState);
            }           
        }
    }

    _lastState = state;
}