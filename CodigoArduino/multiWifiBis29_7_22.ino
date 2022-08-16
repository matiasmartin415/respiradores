#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

void setup() 
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  wifiMulti.addAP("MERCUSYS_E248", "matiasmartin415");
  wifiMulti.addAP("Speedy-F8CA84", "2064421248");
  wifiMulti.addAP("TeleCentro-0522", "KTZWUJZ3EWMM");

}

void loop()
{
  wifiMulti.run();
}

  // Mostrar mensaje de exito, WiFI conectada y dirección IP asignada
/*  Serial.println();
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());*/

  
