#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
boolean connectionWasAlive=true;

void setup() 
{
  Serial.begin(115200);
  Serial.println();

  
  wifiMulti.addAP("MERCUSYS_E248", "matiasmartin415");
  wifiMulti.addAP("Speedy-F8CA84", "2064421248");
  wifiMulti.addAP("TeleCentro-0522", "KTZWUJZ3EWMM");
}

void monitorWifi()
{
  if(wifiMulti.run()!=WL_CONNECTED)
  {
    if(connectionWasAlive==true)
    {
      connectionWasAlive=false;
      Serial.print("Looking for Wifi");
    }
    Serial.print(".");
    delay(500);
  }
  else if(connectionWasAlive==false)
  {
    connectionWasAlive=true;
//   Serial.printf("connected to %s", WiFi.SSID.c_str());
Serial.printf("connected to %s", WiFi.SSID());
  }
}

void loop()
{
  monitorWifi();
}

