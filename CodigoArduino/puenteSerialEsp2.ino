#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

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

  if (mySerial.available()) {
    delay(2);
    int availableBytes = mySerial.available();
    for(int i=0; i<availableBytes; i++)
    {
      enteros[i] = mySerial.read();
      //string[i+1] = '\0'; // Append a null
      recibido[i]=enteros[i];
      Serial.println('recibido');
    }
    //Serial.print('recibido');
    //mensaje = Serial.readString();
    client.publish("test", recibido); // publish: arduino -> mqtt bus

}
/*  if (mySerial.available()){
    delay(2);
   // Serial.println();
   int availableBytes = mySerial.available();
   //Serial.print(availableBytes);
    inByte = mySerial.read();
    //Serial.write(inByte);
    Serial.println(inByte);   
  
  }
 client.publish("test", inByte);
*/
}

