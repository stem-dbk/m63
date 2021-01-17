/*
 * deze code bevat functies om onnodige herhaling te vermijden
 */


// we geven een naam aan de pinnen om het programma overzichtelijk te houden
int RPWM_Output = 5;  // Forward Level PWM output pin, geconnecteerd met de H-brug
int LPWM_Output = 6;  // Reverse Level PWM output pin, geconnecteerd met de H-brug

// eerste wat het programma eenmalig doet
void setup() {
  // we zeggen aan de brainbox (Arduino) dat de twee PWM-pinnen output zijn (analoog), omdat je iets verstuurt
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
  Serial.begin(9600);
}

// dit wordt herhaald
void loop() {
  int x;                                    // initializeer variabele x

  // vooruit
  draai(true, 0, true);
  draai(true, 255, false);
  delay(1000);
  
  for(x = 255; x >= 0; x -= 20){
    draai(true, x, false);
    Serial.print(x);
    Serial.print("\nVooruit \n");
    delay(100);
  }
  
  // achteruit
  draai(false, 0, true);
  draai(false, 255, false);
  delay(1000);
    for(x = 255; x >= 0; x -= 20){
    draai(false, x, false);
    Serial.print(x);
    Serial.print("\nVooruit \n");
    delay(100);
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
