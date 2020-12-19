/* WiFi toegangspunt aanmaken en webserver draaien */

/* biblioteheken die de code vergemakelijken (voorgeprogrammeerde functies) */
#include <ESP8266WiFi.h>        // algemene ESP8266 functies
#include <WiFiClient.h>         // Client functies (nodig?)
#include <ESP8266WebServer.h>   // Server functies
#include <ESP8266mDNS.h>        // DNS = Domain Name System

/* vervang volgende woorden wanneer ze in het programma voorkomen */
#ifndef APSSID                              // check of APPSSID al is gedefinieerd
#define APSSID "My Add On - Demo-Machine"   // definieer SSID (WiFi-naam)
#define APPSK  "MAOdoorDBK"                 // definieer APPSK (wachtwoord, PSK encryptie)
#endif                                      // einde van de check

/* maak ssid en password pointers om later in functies te gebruiken */
const char *ssid = APSSID;      // als ssid in een functie terecht komt, verwijst het naar APSSID
const char *password = APPSK;   // als password in een functie terecht komt, verwijst het naar APPSK

ESP8266WebServer server(80);    // we starten een server op poort 80 (standaard voor HTTP-connectie)
                                // standaard IP van de ESP is http://192.168.4.1 (server hier te vinden)

const int led = LED_BUILTIN;    // variabele led gelijkstellen aan LED_BUILTIN = led ingebouwd in de ESP

/* HTML-code met formulier (onveranderlijke variabele met naam 'postForms') */
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

/* we maken een functie aan om aan te geven wat de server moet versturen en brengen de led op de ESP op nul*/
void handleRoot() {
  server.send(200, "text/html", htmlData);   // verstuur HTTP-status 200 (OK) met HTML-code opgeslagenn in 'htmlData'
}

/* verwerk POST LEDaan bij aanvraag /LEDaan */
void handleLEDaan() {
  digitalWrite(led, 0);                     // leg led aan
  Serial.println("LED aan");                // print dat de led aan is
  server.sendHeader("Location", "/");       // ga terug naar homepage (/)
  server.send(303);                         // verstuur HTTP-status 303 (redirect)
}

/* verwerk POST LEDuit bij aanvraag /LEDuit */
void handleLEDuit() {
  digitalWrite(led, 1);                     // leg led uit
  Serial.println("LED uit");                // print dat de led uit is
  server.sendHeader("Location", "/");       // ga terug naar homepage (/)
  server.send(303);                         // verstuur HTTP-status 303 (redirect)
}

/* wat te doen als niet gevonden */
void handleNotFound() {
  digitalWrite(led, 1);
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
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);         // led is output
  delay(1000);                  // wacht 1 seconde
  Serial.begin(115200);         // maak seriële poort aan met baud 115200 (baud = aantal signaalwisselingen per seconde)
  /* ^ VERANDER OOK BAUD IN SERIELE MONITOR ^ */
  Serial.println();             // print nieuwe lijn op seriële poort
  Serial.print("Configuring access point...");  // print ""
  WiFi.softAP(ssid, password);  // start een toeganspunt (AP) op met naam en wachtwoord die we eerder instelden

  IPAddress myIP = WiFi.softAPIP();         // verkrijg IP van het toegangspunt
  Serial.print("AP IP address: ");          // print ""
  Serial.println(myIP);                     // print IP-addres van het toeganspunt
  /*server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");*/

  /* DNS (netwerk gedeelte) */
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", HTTP_GET, handleRoot);

  server.on("/LEDaan", HTTP_POST, handleLEDaan);

  server.on("/LEDuit", HTTP_POST, handleLEDuit);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
