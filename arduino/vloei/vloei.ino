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
int hasRun = false;       // maak variabele aan om te checken of programma al gedraaid heeft

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

  draai("omlaag", 35, false, 0);          // draai eerst omlaag aan snelheid 50

  // als eindeloopschakelaar 1 wordt ingedrukt (1, HIGH), verander variabele "stand" naar omhoog
  if(digitalRead(eind1) == 1) {
    stand = "omhoog"; 
  }

  // als eindeloopschakelaar 2 wordt ingedrukt (1, HIGH), verander variabele "stand" naar omlaag
  if(digitalRead(eind2) == 1) {
    stand = "omlaag";
  }

  // voer het volgende uit zolang de stand gelijk is aan "omhoog"
  // fout met hasRun = gaat direct over naar hasRun = true en stopt (?) (nee normaal niet)
  while(stand == "omhoog"){
    if(hasRun == false) {           // als hasRun false is
      Serial.println(hasRun);
      vloeiStop(50 ,"omlaag", 25);      // stop vloeiend van de "omlaag" stand, startend met snelheid 50
      draai(stand, 0, true, 150);        // start vloeiend omhoog tot snelheid 255
      hasRun = true;                // verander hasRun naar true, om niet nog een keer vloeiend
    }                               // te draaien vanaf snelheid 0
    draai(stand, 150, false, 0);       // draai omhoog aan snelheid 255
    /*Serial.println(stand);          // print de stand op de seriële monitor*/
    if(digitalRead(eind2) == 1){    // als de tweede eindeloopschakelaar wordt ingedrukt
      stand = "omlaag";             // verander de stand naar "omlaag"
      hasRun = false;               // verander hasRun naar false om volgende keer vloeiend te stoppen
    }                               // de while-lus wordt dan ook afgebroken
  }

  // voer het volgende uit zolang de stand gelijk is aan "omlaag"
  while(stand == "omlaag"){
    if(hasRun == false){            // als hasRun false is
      Serial.println(hasRun);
      vloeiStop(150, "omhoog", 25);     // stop vloeiend van de "omhoog" stand, startend met snelheid 255
      draai(stand, 0, true, 35);        // start vloeiend achteruit tot snelheid 50
      hasRun = true;                // verander hasRun naar true, om niet nog een keer vloeiend
    }                               // te draaien vanaf snelheid 0
    draai(stand, 35, false, 0);        // draai achteruit aan snelheid 50
    /*Serial.println(stand);    // print op de seriele monitor "achteruit"*/
    if(digitalRead(eind1) == 1){    // als de eerste eindeloopschakelaar opnieuw wordt ingedrukt
      stand = "omhoog";            // verander de stand naar "vooruit"
      hasRun = false;               // verander hasRun naar false om volgende keer vloeiend te draaien
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
int draai(int stand, int snelheid, int vloei, int vloeiSnelheid) {
  if (stand == "omhoog"){                                         // als waarde vooruit true is
    if (vloei == true){                                         // als waarde vloei true is
      // doe het volgende voor iedere snelheid tot snelheid < of = 255 en pas snelheid telkens met 10 aanµ
      while(snelheid <= vloeiSnelheid) {
        motor(0, snelheid);
        Serial.println(snelheid);
        snelheid += 5;
        delay(50);
      }
    }
    else {                                                      // als waarde vloei niet true is
        motor(0, snelheid);                                     // draai aan vaste snelheid meegegeven in parameter
        Serial.println(snelheid);
    }
  }
  else if (stand == "omlaag") {                                                        // als waarde vooruit niet true is
    if (vloei == true){                                         // als waarde vloei true is
      while(snelheid <= vloeiSnelheid) {
        motor(snelheid, 0);
        Serial.println(snelheid);
        snelheid += 5;
        delay(50);
      }
    }
    else {                                                      // als waarde vloei niet true is (false)
      motor(snelheid, 0);                                       // draai achteruit aan vaste snelheid
      Serial.println(snelheid);
    }
  }
} 

// een functie om vloeiend te stoppen
int vloeiStop(int remSnelheid, int remStand, int remTijd){
  // doe het volgende voor iedere remSnelheid tot remSnelheid < of = 0 en verminder telkens met 10
  if(remStand == "omlaag"){
    while(remSnelheid >= 0) {
      motor(remSnelheid, 0);
      Serial.println(remSnelheid);
      remSnelheid -= 5;
      delay(remTijd);
    } 
  } else if (remStand == "omhoog"){                           // als remStand "omhoog" is
     while(remSnelheid >= 0) {
      motor(0, remSnelheid);
      Serial.println(remSnelheid);
      remSnelheid -= 5;
      delay(remTijd);
    }
  }
}
