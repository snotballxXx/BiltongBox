/*                                                                    
 ______  _ _ _                       ______             
(____  \(_) (_)_                    (____  \            
 ____)  )_| |_| |_  ___  ____   ____ ____)  ) ___ _   _ 
|  __  (| | | |  _)/ _ \|  _ \ / _  |  __  ( / _ ( \ / )
| |__)  ) | | | |_| |_| | | | ( ( | | |__)  ) |_| ) X ( 
|______/|_|_|_|\___)___/|_| |_|\_|| |______/ \___(_/ \_)
                              (_____|                   
 _  _  _                           _____    __    ______  _       _ 
| || || |                         (____ \  /  |  |  ___ \(_)     (_)
| || || | ____ ____   ___   ___    _   \ \/_/ |  | | _ | |_ ____  _ 
| ||_|| |/ _  )    \ / _ \ /___)  | |   | | | |  | || || | |  _ \| |
| |___| ( (/ /| | | | |_| |___ |  | |__/ /  | |  | || || | | | | | |
 \______|\____)_|_|_|\___/(___/   |_____/   |_|  |_||_||_|_|_| |_|_|
 Created by http://www.network-science.de/ascii/ (stop)
	   
  Pin Out                        _______________	   
                                (               )
                               (       ____      )
                          RST  | o    |    |   o | TX
  FAN RPM DEMAND -------- A0   | o    |____|   o | RX
  LIGHT STRIP OUTPUT ---- D0   | o             o | D1
  LIGHT STRIP PUSH ------ D5   | o             o | D2
  FAN RPM ACTUAL -------- D6   | o             o | D3
  PWM FAN SPEED OUT ----- D7   | o             o | D4
                          D8   | o             o | GND
                          3v3  | o             o | 5v
                               |      _____      |
                               (     |     |     )
                                (____|     |____)
                                     |_____|

This project controls a biltong box, main control is a fan driven by a pot value.
We also have temp and humid monitoring. Additionally there is light switch for LED strip.
It exposes data to prometheus/grafana via a web server running on port 8080
*/
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