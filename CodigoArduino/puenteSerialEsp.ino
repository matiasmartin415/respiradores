#include <SoftwareSerial.h>

SoftwareSerial mySerial(13, 15, false, 256);
 
//Mas informacion http://pdacontroles.com/
// More info http://pdacontrolen.com/ 
 
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(19200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Connect! - Conexion ");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);  
  mySerial.println("Connect! - Conexion SOFTWARESERIAL");
}
 
void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}
