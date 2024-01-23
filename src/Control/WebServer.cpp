#include <arduino.h>
#include "WebServer.h"
#include "../Constants.h"
#include "../Interfaces/ITempRhSensor.h"
#include "../Interfaces/IFanManager.h"

using namespace Control;

WebServer* WebServer::_instance = nullptr;

WebServer::WebServer(Interfaces::ITempRhSensor* tempRhSensor, Interfaces::IFanManager* fanManager) :
     _tempRhSensor(tempRhSensor),
     _fanManager(fanManager),
    _ipAddress("N/C")
{
    _webserver = new ESP8266WebServer(WEB_PORT);

    _instance = this;
    //Begin WiFi
    Serial.print("Begin WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) 
    { 
      Serial.print(".");
      delay(100); 
    }

    // WiFi Connected
    _ipAddress = WiFi.localIP().toString();
    Serial.println(_ipAddress);
    // Start Web Server
    _webserver->on("/", RootPage);
    _webserver->on("/metrics", MetricsPage);
    _webserver->onNotFound(NotfoundPage);
    _webserver->begin();  
}

void WebServer::Loop(unsigned long now)
{
    _webserver->handleClient();
}

// Handle Metrics
void WebServer::MetricsPage() 
{ 
  float temp, rh;

  _instance->_tempRhSensor->GetData(temp, rh);

  int rpm = _instance->_fanManager->GetFanData();

  String data = "# HELP temperature_centigrade_float current temperature\n# TYPE temperature_centigrade_float gauge\ntemperature_centigrade_float " + String(temp) + "\n";
  String humidity = "# HELP humidity_rh_float current relative humidity\n# TYPE humidity_rh_float gauge\nhumidity_rh_float " + String(rh) + "\n";
  data.concat(humidity);
  data.concat("# HELP rpm_actual_int current rpm\n# TYPE rpm_actual_int gauge\nrpm_actual_int " + String(rpm)  + "\n");
  data.concat("# HELP rpm_demand_int demand rpm\n# TYPE rpm_demand_int gauge\nrpm_demand_int " + String(_instance->_fanManager->GetFanDemand()) + "\n");
  
  _instance->_webserver->send(200, "text/plain", data.c_str()); 
}

void WebServer::RootPage() 
{ 
  float temp, rh;
  _instance->_tempRhSensor->GetData(temp, rh);

  String data = "temp = ";
  data.concat(String(temp).c_str());
  data.concat(", rh = ");
  data.concat(String(rh).c_str());

  _instance->_webserver->send(200, "text/plain", String(data).c_str()); 
}

// Handle 404
void WebServer::NotfoundPage()
{ 
  _instance->_webserver->send(404, "text/plain", "404: Not found"); 
}