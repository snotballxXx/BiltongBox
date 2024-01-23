#include "./src/Control/WebServer.h"
#include "./src/Control/TempRhSensor.h"
#include "./src/Control/FanManager.h"
#include "./src/Control/FanRpmMonitor.h"
#include "./src/Control/ToggleOutput.h"

Control::WebServer* webServer;
Control::TempRhSensor* tempRhSensor;
Control::FanManager* fanManager;
Control::ToggleOutput* toggleOutput;
Interfaces::IFanRpmMonitor* monitor;

void setup()
{
    Serial.begin(115200);

    monitor = new Control::FanRpmMonitor(D6);
    tempRhSensor = new Control::TempRhSensor();
    fanManager = new Control::FanManager(D7, monitor);
    webServer = new Control::WebServer(tempRhSensor, fanManager);
    toggleOutput = new Control::ToggleOutput(D5, D0);
}

void loop(void) 
{   
    unsigned long now = millis(); 
    tempRhSensor->Loop(now);
    fanManager->Loop(now);
    webServer->Loop(now);
    toggleOutput->Loop(now);
}