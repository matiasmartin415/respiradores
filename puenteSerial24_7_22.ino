#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <String>

SoftwareSerial mySerial(13, 15);
char inByte;

const char* ssid = "Speedy-F8CA84";
const char* password = "2064421248";
const char* mqtt_server = "192.168.1.36";

String stringUno, stringDos; 



WiFiClient espClient;
PubSubClient client(espClient);
char recibido[50];
int enteros[50];
String mensaje;
int byteRead;

char caracter;
char vector[300];
char vectorCompleto[300];
char vectorConcatenado[350];
int i=2;
unsigned long prev=0; 


void setup() {

  stringUno=String("datos iniciales");
  stringDos=String();
//  vectorCompleto=char();
  
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(19200);
  mySerial.begin(19200); 
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

                            vector[0]= 'A';
                            vector[1]= ':';

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
  //  Serial.print((char)payload[i]);//no gasto tiempo imprimiendo por monitor
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

//while(!Serial.available());

  if (Serial.available()) {
                            delay(4);

                          //  caracter=Serial.write(Serial.read());
                           // vector[i]=caracter;
                             
                           vector[i]=Serial.read();
                            i=i+1;
                           }else{
                                //vector[i]=NULL;
                                i=2;
                             //   client.publish("test", caracter); // publish: arduino -> mqtt bus 
                             //   client.publish("test", vector);
                                }
                            
if (millis()-prev > 3000){
    prev=millis();
    //Serial.write(vector);
    delay(10); //la pausa mejora la comunicacion
    //vectorConcatenado[0]=ssid;
    // vectorConcatenado=strset(vector,ssid);
    //vectorConcatenado=vectorConcatenado.concat(ssid);
stringDos = stringUno + ssid;
stringDos = vector + 'ssid';
//vectorCompleto = vector + 'ssid';
//strcpy(vector,vectorCompleto);
//strcpy(vectorCompleto,vector +'ssid');
//strcat(vector,ssid);

strcpy(vectorCompleto,ssid);
strcat(vectorCompleto,vector);

//stringDos.toCharArray(vectorCompleto,300);
    //client.publish("test", vector);
  //  client.publish("test", vectorConcatenado);
    client.publish("test", vectorCompleto);
   
                         }else{
                            
                                }


}
