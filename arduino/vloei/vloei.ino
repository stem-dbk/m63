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
  int x;

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

int motor(int vsnel, int asnel){
  analogWrite(LPWM_Output, vsnel);
  analogWrite(RPWM_Output, asnel);
}

int draai(int vooruit, int snelheid, int vloei) {
  if (vooruit == true){
    if (vloei == true){
      for(snelheid = 1; snelheid <= 255; snelheid += 10){
        motor(snelheid, 0);
      }
    }
    else {
        motor(snelheid, 0);
    }
  }
  else {
    if (vloei == true){
      for(snelheid = 1; snelheid <= 255; snelheid += 10){
        motor(0, snelheid);
      }
    }
    else {
      motor(0, snelheid);
    }
  }
}
