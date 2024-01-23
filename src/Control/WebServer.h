#ifndef __WEB_SERVER__H__
#define __WEB_SERVER__H__

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "../Interfaces/IWebServer.h"


namespace Interfaces
{
    class ITempRhSensor;
    class IFanManager;
}

namespace Control
{    
    class WebServer : public Interfaces::IWebServer
    {
        ESP8266WebServer* _webserver;
        String _ipAddress;

        Interfaces::ITempRhSensor* _tempRhSensor;
        Interfaces::IFanManager* _fanManager;

        public:
        WebServer(Interfaces::ITempRhSensor* tempRhSensor, Interfaces::IFanManager* _fanManager);
        void Loop(unsigned long now);

        static void MetricsPage();
        static void RootPage();
        static void NotfoundPage();
        static WebServer* _instance;

        String GetIpAddress() { return _ipAddress; };
    };
}
#endif  //!__WEB_SERVER__H__