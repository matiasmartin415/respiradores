#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
//#include <WiFiMulti.h>

SoftwareSerial mySerial(13, 15);
char inByte;

const char* ssid = "Speedy-F8CA84";
const char* password = "2064421248";
const char* mqtt_server = "192.168.1.36";

WiFiClient espClient;
PubSubClient client(espClient);
char recibido[50];
int enteros[50];
String mensaje;
int byteRead;

char caracter;
char vector[300];
int i=2;
unsigned long prev=0; 
int bytesDisponibles=0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(19200);
  mySerial.begin(19200); 
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}

void reconnect() {
  String clientName;
  clientName += "esp8266-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);
  clientName += "-";
  clientName += String(micros() & 0xff, 16);
  while (!client.connected()) {
                              if (client.connect((char*) clientName.c_str())) { // random client id
                                digitalWrite(BUILTIN_LED, LOW); // low = high, so this turns on the led
                                client.subscribe("test"); // callback: mqtt bus -> arduino
                              } else {
                                digitalWrite(BUILTIN_LED, HIGH); // high = low, so this turns off the led
                                delay(5000);
                                      }
                              }
}

void loop() {
  if (!client.connected()) {
                            reconnect();
                            }
  client.loop();

 if (Serial.available()) {
                            delay(2);
                            bytesDisponibles=Serial.available();
                            vector[0]= 'A';
                            vector[1]= ':';

                            for(i=2;i<=20;i++){
                                          vector[i]=Serial.read();
                                          }
                               

                           }else{
                                i=2;
                                }
                            
                            
                            
if (millis()-prev > 3000){
    prev=millis();
    //Serial.write(bytesDisponibles);
    client.publish("test", vector); 
                         }else{
                            
                                }


}

