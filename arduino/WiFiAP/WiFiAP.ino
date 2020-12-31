/* 
 *  Doel: WiFi toegangspunt aanmaken en webserver draaien om builtin LED te laten branden
 *  Benodigdheden: ESP8266 (hardware), board beheer: http://arduino.esp8266.com/stable/package_esp8266com_index.json (software)
 *  Meer info: https://stem-dbk.github.io/m63
 *  
 *  communicatie tussen Arduino's nog niet gelukt
 */

/* biblioteheken die de code vergemakelijken (voorgeprogrammeerde functies) */
#include <ESP8266WiFi.h>        // algemene ESP8266 functies
#include <ESP8266WebServer.h>   // Server functies

/* bibliotheek voor communicatie tussen Arduino's */
//#include <Wire.h>

/* definieer het addres voor I2C communicatie */
//#define I2CAddressESPWifi 8

/* vervang volgende woorden wanneer ze in het programma voorkomen */
#ifndef APSSID                              // check of APPSSID al is gedefinieerd, als dat niet zo is doe het volgende:
#define APSSID "My Add On - Demo-Machine"   // definieer SSID (WiFi-naam)
#define APPSK  "MAOdoorDBK"                 // definieer APPSK (wachtwoord, PSK-encryptie)
#endif                                      // einde van de check

/* maak ssid en password pointers om later in functies te gebruiken */
const char *ssid = APSSID;      // als ssid in een functie terecht komt, verwijst het naar variabele APSSID
const char *password = APPSK;   // als password in een functie terecht komt, verwijst het naar variabele APPSK

ESP8266WebServer server(80);    // we starten een server op poort 80 (standaard voor HTTP-connectie)
                                // standaard IP van de ESP is http://192.168.4.1 (webserver hier te vinden)

const int led = LED_BUILTIN;    // variabele led gelijkstellen aan LED_BUILTIN = led ingebouwd in de ESP = 2

/* opnieuw voor I2C-communicatie */
String bericht;                 // maak variabele "bericht" aan als string (letters)
//boolean statusLed;

/* HTML-code met formulier (onveranderlijke variabele met naam 'htmlData') */
const String htmlData = "<html>\
  <head>\
    <title>My Add On | Demo-Machine | bediening</title>\
    <style>\
      body { background-color: white; font-family: Arial, Helvetica, Sans-Serif; color: #3a3a3a; }\
      .button { background-color: rgb(234, 174, 61); color: white; border: none; padding: 15px 32px; text-align: center; display: inline-block; font-size: 25px;}\
    </style>\
  </head>\
  <body>\
    <h1>Bedien LED</h1><br>\
    <form action=\"/LEDaan\" method=\"POST\">\
      <input class=\"button\" type=\"submit\" value=\"LED aan\">\
    </form>\
    <form action=\"/LEDuit\" method=\"POST\">\
      <input class=\"button\" type=\"submit\" value=\"LED uit\">\      
    </form>\
  </body>\
</html>";


/* we maken een functie aan om aan te geven wat de server moet versturen wanneer die functie wordt aangeroepen*/
void handleRoot() {
  server.send(200, "text/html", htmlData);  // verstuur HTTP-status 200 (OK) met HTML-code opgeslagen in 'htmlData'
}

/* verwerk POST LEDaan bij aanvraag /LEDaan */
void handleLEDaan() {
  digitalWrite(led, 0);                     // leg led aan
  
  bericht = "Led is aangestoken";           // verander inhoud variabele "bericht"

  /* I2C-communicatie */
  /*Wire.beginTransmission(I2CAddressESPWifi);
  Wire.write("testaan");
  Wire.endTransmission();*/

  Serial.println(bericht);                  // print het bericht
  server.sendHeader("Location", "/");       // ga terug naar homepage (/) van de webserver
  server.send(303);                         // verstuur HTTP-status 303 (redirect)
}

/* verwerk POST LEDuit bij aanvraag /LEDuit */
void handleLEDuit() {
  digitalWrite(led, 1);                     // leg led uit
  bericht = "Led is uitgeschakeld";

  /* I2C-communicatie */
  //Wire.write("testuit");
  
  Serial.println(bericht);                  // print het bericht
  server.sendHeader("Location", "/");       // ga terug naar homepage (/) van de webserver
  server.send(303);                         // verstuur HTTP-status 303 (redirect)
}

/* wat te doen als aanvrag niet gevonden */
void handleNotFound() {
  //digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  Serial.print(message);
  server.send(404, "text/plain", message);  // verstuur HTTP-status 404 (not found)
  //digitalWrite(led, 0);                     // leg led aan
}

/* I2C- communicatie */
/*void stuurBericht() {
  Wire.write("test");
  Serial.print("'stuurBericht' is geactiveerd");
}*/

void setup(void) {
  pinMode(led, OUTPUT);         // led is output
  
  /* I2C-communicatie */
  //Wire.begin(0, 2);
  
  Serial.begin(115200);         // zet seriële poort met baud rate 115200 op (baud = aantal signaalwisselingen per seconde)
  /* ^ VERANDER OOK BAUD IN SERIELE MONITOR ^ */
  Serial.println();             // print nieuwe lijn op seriële poort
  Serial.print("Configuring access point...");  // print ""
  WiFi.softAP(ssid, password);  // start een toeganspunt (AP) op met naam en wachtwoord die we eerder configureerden

  IPAddress myIP = WiFi.softAPIP();         // verkrijg IP van het toegangspunt en stel die in als variabele myIP
  Serial.print("AP IP address: ");          // print ""
  Serial.println(myIP);                     // print IP-addres van het toeganspunt

  server.on("/", HTTP_GET, handleRoot);             // wanneer pagina (home) "/" wordt aangeroepen via webserver, voer functie handleRoot uit

  server.on("/LEDaan", HTTP_POST, handleLEDaan);    // wanneer pagina "/LEDaan" wordt aangeroepen via webserver, voer functie handleLEDaan uit

  server.on("/LEDuit", HTTP_POST, handleLEDuit);    // wanneer pagina "/LEDuit" wordt aangeroepen via webserver, voer functie handleLEDuit uit

  server.onNotFound(handleNotFound);                // wanneer aanvraag niet gevonden wordt, voer functie "handleNotFound" uit

  server.begin();                                   // start server
  Serial.println("HTTP server started");            // print op een nieuwe lijn dat de server gestart is
}

void loop(void) {
  server.handleClient();                            // houd de server constant in de gaten
}
