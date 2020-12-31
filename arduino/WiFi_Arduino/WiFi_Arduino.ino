/* #include <SoftwareSerial.h>       // bibliotheek met serial functies om serial van de ESP8266 uit te lezen
#define RX 10                     // de RX (receive) van de ESP zit aan poort 10
#define TX 11                     // de TX (transmit) van de ESP zit aan poort 11
SoftwareSerial esp8266(RX,TX);    // */

/* bibliotheek voor communicatie tussen Arduino's */
#include <Wire.h>
#define I2CAddressESPWifi 8

char response[11] = "0123456789";

void espWifiReceiveEvent(int count)
{
Serial.print("Received[");
while (Wire.available())
{
char c = Wire.read();
Serial.print(c);
}
Serial.println("]");
//calc response.
}

void espWifiRequestEvent()
{
Wire.write(response);
}

/* Deze code wordt 1 keer uitgevoerd */
void setup() {
  Wire.begin(I2CAddressESPWifi);
  Serial.begin(115200);           // we starten een seriele communicatie met baud rate 9600
  Wire.onReceive(espWifiReceiveEvent);
  Wire.onRequest(espWifiRequestEvent);
  Serial.println("Connection with ESP8266 test");
}

/* Deze code wordt herhaald */
void loop() {
  delay(500);
}
