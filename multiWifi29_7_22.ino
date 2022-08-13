#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
boolean connectionWasAlive=true;

void setup() 
{
  Serial.begin(115200);
  Serial.println();

  wifiMulti.addAP("Speedy-F8CA84", "2064421248");
  wifiMulti.addAP("TeleCentro-0522", "KTZWUJZ3EWMM");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");
}

void monitorWifi()
{
  if(wifiMulti.run()!=WL_CONNECTED)
  {
    if(cennectionWasAlive==true)
    {
      connectionWasAlive=false;
      Seral.print("Looking for Wifi");
    }
    Serial.print(".");
    delay(500);
  }
  else if(connectionWasAlive==false)
  {
    connectionWasAlive=true;
    Serial.printf("connected to %s",WiFi.SSID.c_str());
  }
}

void loop()
{
  monitorWifi();
}

