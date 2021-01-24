/*
 * deze code bevat functies om onnodige herhaling te vermijden
 */


// we geven een naam aan de pinnen om het programma overzichtelijk te houden
int RPWM_Output = 5;  // Forward Level PWM output pin, geconnecteerd met de H-brug
int LPWM_Output = 6;  // Reverse Level PWM output pin, geconnecteerd met de H-brug

const int eind1 = 21;   // pin van input eerste eindeloopschakelaar
const int eind2 = 22;   // pin van input tweede eindeloopschakelaar

// maak variabele aan voor status shakelaars
char eind1Status = 0;
char eind2Status = 0;

int x;

// eerste wat het programma eenmalig doet
void setup() {
  // we zeggen aan de brainbox (Arduino) dat de twee PWM-pinnen output zijn (analoog), omdat je iets verstuurt
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);

  pinMode(eind1, INPUT);
  pinMode(eind2, INPUT);
  Serial.begin(9600);

  if(eind1Status == 0 && eind2Status == 0){
    while(eind1Status != 1){
      draai(true, 100, false);                // draai vooruit om krukken in beginstand te zetten
    }
  }
}

// dit wordt herhaald
void loop() {

  if(eind1Status == 1) {                      // als eindeloopschakelaar 1 wordt ingedrukt, draai vooruit
    // vooruit
    draai(true, 0, true);                     // vloeiend vooruit
    draai(true, 255, false);                  // 1s op vaste snelheid
    delay(1000);    

    // vooruit afremmen
    for(x = 255; x >= 0; x -= 20){
      draai(true, x, false);
      Serial.print(x);
      Serial.print("\nVooruit \n");
      delay(100);
    }
  }

  if(eind2Status == 1) {                      // als eindeloopschakelaar 2 wordt ingedrukt, draai achteruit
    // achteruit
    draai(false, 0, true);
    draai(false, 255, false);
    delay(1000);

    // achteruit remmend
    for(x = 255; x >= 0; x -= 20){
      draai(false, x, false);
      Serial.print(x);
      Serial.print("\nVooruit \n");
      delay(100);
      }    
  }
}


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
        motor(snelheid, 0);                                     // draai aan vaste snelheid
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
