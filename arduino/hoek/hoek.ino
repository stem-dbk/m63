// we geven een naam aan de pinnen om het programma overzichtelijk te houden
int RPWM_Output = 5;  // Forward Level PWM output pin, geconnecteerd met de H-brug
int LPWM_Output = 6;  // Reverse Level PWM output pin, geconnecteerd met de H-brug

int var = 1;

// eerste wat het programma eenmalig doet
void setup() {
  
  // we zeggen aan de brainbox (Arduino) dat de twee PWM-pinnen output zijn (analoog), omdat je iets verstuurt
  pinMode(RPWM_Output, OUTPUT); 
  pinMode(LPWM_Output, OUTPUT);

}

// dit wordt herhaald
void loop() {
  // voorlopige oplossing: synchronisatie is niet correct
  
  // de motor 745 ms vooruit laten draaien
  // 0 = stilstaan; 1000 is bijna aan volle kracht (1023) draaien
  
  analogWrite(LPWM_Output, 1000);
  analogWrite(RPWM_Output, 0);
  delay(745);

  // 1 s niet draaien
  analogWrite(RPWM_Output, 0);
  analogWrite(LPWM_Output, 0);
  delay(1000);

  // 820 ms achteruit draaien
  analogWrite(LPWM_Output, 0);
  analogWrite(RPWM_Output, 1000);
  delay(820);

  // 1 s niet draaien
  analogWrite(RPWM_Output, 0);
  analogWrite(LPWM_Output, 0);
  delay(1000);

}
