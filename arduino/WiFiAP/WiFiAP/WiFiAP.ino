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
const String postForms = "<html>\
  <head>\
    <title>My Add On | Demo-Machine | bediening</title>\
    <style>\
      body { background-color: black; font-family: Arial, Helvetica, Sans-Serif; Color: white; }\
    </style>\
  </head>\
  <body>\
    <h1>'plain' data naar /postplain/</h1><br>\
    <form method=\"post\" enctype=\"text/plain\" action=\"/postplain/\">\
      <input type=\"text\" name=\'\"\' value=\'\"}\'><br>\
      <input type=\"submit\" value=\"Verzend\">\
    </form>\
    <h1>'form' data naar /postform/</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/postform/\">\
      <input type=\"text\" name=\"hello\" value=\"world\"><br>\
      <input type=\"submit\" value=\"Verzend\">\
    </form>\
  </body>\
</html>";

/* we maken een functie aan om aan te geven wat de server moet versturen en brengen de led op de ESP op nul*/
void handleRoot() {
  digitalWrite(led, 1);                      // LED aan
  server.send(200, "text/html", postForms);  // verstuur HTTP-status 200 (OK) met HTML-code opgeslagenn in 'postForms'
  digitalWrite(led, 0);                      // LED uit
  
}

/* verwerk POST plain */
void handlePlain() {
  if (server.method() != HTTP_POST) {
    digitalWrite(led, 1);
    server.send(405, "text/plain", "Method Not Allowed");
    digitalWrite(led, 0);
  } else {
    digitalWrite(led, 1);
    server.send(200, "text/plain", "POST body was:\n" + server.arg("plain"));
    digitalWrite(led, 0);
  }
}

/* verwerk POST formulier */
void handleForm() {
  if (server.method() != HTTP_POST) {
    digitalWrite(led, 1);
    server.send(405, "text/plain", "Method Not Allowed");
    digitalWrite(led, 0);
  } else {
    digitalWrite(led, 1);
    String message = "POST form was:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      Serial.println(i);  // REV ENG
      Serial.print("" + server.argName(i) + " " + server.arg(i)); // REV ENG : voor ieder arg (argument?) wordt de naam en data verkregen
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(200, "text/plain", message);
    digitalWrite(led, 0);
    //Serial.println(server.args());
    Serial.println(message);
  }
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
  digitalWrite(led, 0);         // led uit
  delay(1000);                  // wacht 1 seconde
  Serial.begin(115200);         // maak seriële poort aan met baud 115200 (baud = aantal signaalwisselingen per seconde)
  Serial.println();             // print nieuwe lijn op seriële poort
  Serial.print("Configuring access point...");  // print ""
  WiFi.softAP(ssid, password);  // start een toeganspunt (AP) op met naam en wachtwoord die we eerder instelden

  IPAddress myIP = WiFi.softAPIP();         // verkrijg IP van het toegangspunt
  Serial.print("AP IP address: ");          // print ""
  Serial.println(myIP);                     // print IP-addres van het toeganspunt
  /*server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");*/

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/postplain/", handlePlain);

  server.on("/postform/", handleForm);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
