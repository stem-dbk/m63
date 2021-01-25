 /*
  * deze code bevat functies om onnodige herhaling te vermijden
  */

// we geven een naam aan de pinnen om het programma overzichtelijk te houden
int RPWM_Output = 5;      // Forward Level PWM output pin, geconnecteerd met de H-brug
int LPWM_Output = 6;      // Reverse Level PWM output pin, geconnecteerd met de H-brug

const int eind1 = 21;     // pin van input eerste eindeloopschakelaar
const int eind2 = 22;     // pin van input tweede eindeloopschakelaar

// maak variabele aan voor status shakelaars
char eind1Status = 0;     // variabele voor status eindeloopschakelaar 1
char eind2Status = 0;     // variabele voor status eindeloopschakelaar 2

int stand;                // maak variabele "stand" aan voor de status van de eindeloopschakelaars

// eerste wat het programma eenmalig doet
void setup() {
  // we zeggen aan de brainbox (Arduino) dat de twee PWM-pinnen output zijn (analoog), omdat je iets verstuurt
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);

  // de eindeloopschakelaar geeft ons een bepaalde input, dus we stellen deze in als input
  pinMode(eind1, INPUT);    // eindeloopschakelaar 1
  pinMode(eind2, INPUT);    // eindeloopschakelaar 2

  // we starten een seriele monitor om te zien wat het programma doet
  Serial.begin(9600);
}

// dit wordt herhaald
void loop() {

  draai(true, 200, false);          // draai eerst vooruit aan snelheid 200

  // als eindeloopschakelaar 1 wordt ingedrukt (1, HIGH), verander variabele "stand" naar vooruit
  if(digitalRead(eind1) == 1) {
    stand = "vooruit"; 
  }

  // als eindeloopschakelaar 2 wordt ingedrukt (1, HIGH), verander variabele "stand" naar achteruit
  if(digitalRead(eind2) == 1) {
    stand = "achteruit";
  }

  // voer het volgende uit zolang de stand gelijk is aan "vooruit"
  while(stand == "vooruit"){
    draai(true, 255, false);        // draai vooruit aan snelheid 255
    Serial.println("vooruit");      // print op de seriele monitor "vooruit"
    if(digitalRead(eind2) == 1){    // als de tweede eindeloopschakelaar wordt ingedrukt
      stand = "achteruit";          // verander de stand naar "achteruit"
    }                               // de while-lus wordt dan ook afgebroken
  }

  // voer het volgende uit zolang de stand gelijk is aan "achteruit"
  while(stand == "achteruit"){
    draai(false, 50, false);        // draai achteruit aan snelheid 50
    Serial.println("achteruit");    // print op de seriele monitor "achteruit"
    if(digitalRead(eind1) == 1){    // als de eerste eindeloopschakelaar opnieuw wordt ingedrukt
      stand = "vooruit";            // verander de stand naar "vooruit"
    }                               // de while-lus wordt dan ook afgebroken
  }
}

/*
 * we maken gebruik van eigen functies om het programma flexibeler en eenvoudiger te maken
 * het verandert niets aan de werking
 */

// functie om motor te laten draaien met parameters (vsnel en asnel, die worden geinitializeerd)
int motor(int vsnel, int asnel){
  analogWrite(LPWM_Output, vsnel);            // draai vooruit aan snelheid 'vsnel'
  analogWrite(RPWM_Output, asnel);            // draai achteruit aan snelheid 'asnel'
}

// functie om motor vooruit of achteruit te laten draaien aan bepaalde snelheid
// en hem al dan niet vloeiend laten bewegen volgens parameters (vooruit, snelheid, vloei)
int draai(int vooruit, int snelheid, int vloei) {
  if (vooruit == true){                                         // als waarde vooruit true is
    if (vloei == true){                                         // als waarde vloei true is
      // doe het volgende voor iedere snelheid tot snelheid < of = 255 en pas snelheid telkens met 10 aan
      for(snelheid = 1; snelheid <= 255; snelheid += 10){       
        motor(snelheid, 0);                                     // laat motor aan die snelheid vooruit draaien
      }
    }
    else {                                                      // als waarde vloei niet true is
        motor(snelheid, 0);                                     // draai aan vaste snelheid meegegeven in parameter
    }
  }
  else {                                                        // als waarde vooruit niet true is
    if (vloei == true){                                         // als waarde vloei true is
      for(snelheid = 1; snelheid <= 255; snelheid += 10){       // stel snelheid vloeibaar in
        motor(0, snelheid);                                     // draai achteruit aan snelheid
      }
    }
    else {                                                      // als waarde vloei niet true is (false)
      motor(0, snelheid);                                       // draai achteruit aan vaste snelheid
    }
  }
} 
