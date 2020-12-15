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
  int x; // initialiseer x variabele

  // vooruit
  for(x = 0; x <= 1024; x+=3){
    analogWrite(LPWM_Output, x);
    analogWrite(RPWM_Output, 0);
    Serial.print(x);
    Serial.print("\nVooruit \n");
    delay(25);
  }
  // achteruit
   for(x = 0; x <= 1024; x+=3){
    analogWrite(LPWM_Output, x);
    analogWrite(RPWM_Output, 0);
    Serial.print(x);
    Serial.print("\nAchteruit \n");
    delay(25);
  }
}
