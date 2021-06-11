  /*
  * deze code bevat functies om onnodige herhaling te vermijden
  */

// we geven een naam aan de pinnen om het programma overzichtelijk te houden
int RPWM_Output = 5;      // Forward Level PWM output pin, geconnecteerd met de H-brug
int LPWM_Output = 6;      // Reverse Level PWM output pin, geconnecteerd met de H-brug

const int eind1 = 22;     // pin van input eerste eindeloopschakelaar
const int eind2 = 21;     // pin van input tweede eindeloopschakelaar

const int potentioSen = 18;   // Arduino analog input pin 18 = A18; middelste pinnetje

// maak variabele aan voor status shakelaars
char eind1Status = 0;     // variabele voor status eindeloopschakelaar 1
char eind2Status = 0;     // variabele voor status eindeloopschakelaar 2

int snelOmhoog = 150;     // variabele voor snelheid omhoog, zodat makkelijk aanpasbaar
int snelOmlaag = 35;      // variabele voor snelheid omlaag, zodat makkelijk aanpasbaar

int stand;                // maak variabele "stand" aan voor de status van de eindeloopschakelaars
int hasRun = false;       // maak variabele aan om te checken of programma vloeiend stoppen al gedraaid heeft

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
  
  // draai(stand, snelheid, vloeiend, startsnelheid vloeiende beweging)
  draai("omlaag", potentioOmlaag(), false, 0);          // draai eerst omlaag aan snelheid van variabele snelOmlaag

  // als eindeloopschakelaar 1 wordt ingedrukt (1, HIGH), verander variabele "stand" naar omhoog
  if(digitalRead(eind1) == 1) {
    stand = "omhoog"; 
  }

  // als eindeloopschakelaar 2 wordt ingedrukt (1, HIGH), verander variabele "stand" naar omlaag
  if(digitalRead(eind2) == 1) {
    stand = "omlaag";
  }

  // voer het volgende uit zolang de stand gelijk is aan "omhoog"
  // hasRun = check om vloeiend te stoppen en starten 
  while(stand == "omhoog"){
    if(hasRun == false) {           // als hasRun false is
      Serial.println(hasRun);       // print hasRun status
      vloeiStop(potentioOmlaag() ,"omlaag", 25);      // stop vloeiend in 25ms van "omlaag", startend met huidige snelheid 
      draai(stand, 1, true, potentioOmhoog());        // start vloeiend vanaf snelheid 1 omhoog tot snelheid snelOmhoog
      hasRun = true;                // verander hasRun naar true, om niet nog een keer vloeiend te stoppen en draaien
    }                               
    draai(stand, potentioOmhoog(), false, 0);       // draai omhoog aan snelheid snelOmhoog, niet vloeiend
    if(digitalRead(eind2) == 1){    // als de tweede eindeloopschakelaar wordt ingedrukt
      stand = "omlaag";             // verander de stand naar "omlaag"
      hasRun = false;               // verander hasRun naar false om volgende keer vloeiend te stoppen
    }                               // de while-lus wordt dan ook afgebroken
  }

  // voer het volgende uit zolang de stand gelijk is aan "omlaag"
  while(stand == "omlaag"){
    if(hasRun == false){            // als hasRun false is
      Serial.println(hasRun);       // print hasRun status
      vloeiStop(snelOmhoog, "omhoog", 25);     // stop vloeiend in 25ms van "omhoog", startend met huidige snelheid 
      draai(stand, 1, true, potentioOmlaag());       // start vloeiend vanaf snelheid 1 omlaag tot snelheid snelOmlaag
      hasRun = true;                // verander hasRun naar true, om niet nog een keer vloeiend te draaien
    }                              
    draai(stand, potentioOmlaag(), false, 0);        // draai omlaag aan snelheid snelOmlaag, niet vloeiend
    if(digitalRead(eind1) == 1){    // als de eerste eindeloopschakelaar opnieuw wordt ingedrukt
      stand = "omhoog";             // verander de stand naar "omhoog"
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
  analogWrite(LPWM_Output, vsnel);            // draai omlaag aan snelheid 'vsnel'
  analogWrite(RPWM_Output, asnel);            // draai omhoog aan snelheid 'asnel'
}

// functie om motor oml of achteruit te laten draaien aan bepaalde snelheid
// en hem al dan niet vloeiend laten bewegen volgens parameters (vooruit, snelheid, vloei)
int draai(int stand, int snelheid, int vloei, int vloeiSnelheid) {
  if (stand == "omhoog"){                                       // als stand omhoog is
    if (vloei == true){                                         // als vloei true is
      // vermenigvuldig de snelheid met factor 2 voor iedere snelheid tot 
      // snelheid < of = gewenste snelheid
      while(snelheid <= vloeiSnelheid) {
        motor(0, snelheid);                                     // laat motor omhoog draaien aan "snelheid"
        Serial.println(snelheid);                               // print "snelheid"
        Serial.println("omhoog");
        snelheid += 10;                                          // vermenigvuldig "snelheid" met factor 2
        delay(50);                                              // wacht 50 ms
      }
    }
    else {                                                      // als waarde vloei niet true is (false)
        motor(0, snelheid);                                     // draai omhoog aan vaste snelheid meegegeven in parameter
        Serial.println(snelheid);
    }
  }
  else if (stand == "omlaag") {                                 // als stand omlaag is
    if (vloei == true){                                         // als vloei true is
      // vermenigvuldig de snelheid met factor 2 voor iedere snelheid tot 
      // snelheid < of = gewenste snelheid
      while(snelheid <= vloeiSnelheid) {
        motor(snelheid, 0);                                     // laat motor omlaag draaien aan "snelheid"
        Serial.println(snelheid);                               // print "snelheid"
        Serial.println("omlaag");
        snelheid += 10;                                          // vermenigvuldig "snelheid" met factor 2
        delay(50);                                              // wacht 50 ms
      }
    }
    else {                                                      // als waarde vloei niet true is (false)
      motor(snelheid, 0);                                       // draai omlaag aan vaste snelheid meegegeven in parameter
      Serial.println(snelheid);
    }
  }
} 

// een functie om vloeiend te stoppen
int vloeiStop(int remSnelheid, int remStand, int remTijd){
  // doe het volgende voor iedere remSnelheid tot remSnelheid < of = 0 en verminder telkens met 5
  if(remStand == "omlaag"){                     // als "remStand" omlaag is
    while(remSnelheid >= 0) {                   // zolang remSnelheid groter is dan 0
      motor(remSnelheid, 0);                    // draai omlaag aan remSnelheid
      Serial.println(remSnelheid);              // print "remSnelheid"
      remSnelheid -= 10;                         // verminder remSnelheid met 5
      delay(remTijd);                           // wacht "remTijd" ms
    } 
  } else if (remStand == "omhoog"){             // als "remStand" omhoog is
     while(remSnelheid >= 0) {                  // zolang remSnelheid groter is dan 0
      motor(0, remSnelheid);                    // draai omhoog aan remSnelheid
      Serial.println(remSnelheid);              // print "remSnelheid"
      remSnelheid -= 10;                         // verminder remSnelheid met 5
      delay(remTijd);                           // wacht "remTijd" ms
    }
  }
}

int potentioOmlaag(){
  int potentioVal = analogRead(potentioSen);
  int rangeVal = 512/35;
  if(potentioVal < 512){
    return(35 - (-(potentioVal-512)/rangeVal));
  } else if (potentioVal > 512){
    return(35 + (potentioVal-512)/rangeVal);
  } else if(potentioVal = 512){
    return(35);
  }
}

int potentioOmhoog(){
  int potentioVal = analogRead(potentioSen);
  int rangeVal = 512/35;
  if(potentioVal < 512){
    return(150 - (-(potentioVal-512)/rangeVal));
  } else if (potentioVal > 512){
    return(150 + (potentioVal-512)/rangeVal);
  } else if(potentioVal = 512){
    return(150);
  }
}
