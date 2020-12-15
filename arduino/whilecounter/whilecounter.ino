// we geven een naam aan de pinnen om het programma overzichtelijk te houden
int RPWM_Output = 5;  // Forward Level PWM output pin, geconnecteerd met de H-brug
int LPWM_Output = 6;  // Reverse Level PWM output pin, geconnecteerd met de H-brug

void setup() {
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
  Serial.begin(9600);
}

void loop(à {
  int x; // initialiseer x variabele

  // vooruit
  Serial.print("Vooruit \n");
  x = 0;  // stel x gelijk aan 0
  while (x < 1024) // voer volgend programma uit wanneer x kleiner is dan 1024
  {
    Serial.print(x); // print x
    Serial.print("\n"); // print nieuwe lijn

    analogWrite(LPWM_Output, x);
    analogWrite(RPWM_Output, 0);

    x++; // 1 toevoegen aan x
    delay(25); // wacht 50 ms
  }
  
  // achteruit
  Serial.print("Achteruit \n");
  x = 0; // stel x gelijk aan 0
  while (x < 1024) // voer volgend programma uit wanneer x kleiner is dan 1024
  {
    Serial.print(x); // print x
    Serial.print("\n"); // print nieuwe lijn

    analogWrite(LPWM_Output, 0);
    analogWrite(RPWM_Output, x);

    x++; // 1 toevoegen aan x
    delay(25); // wacht 50 ms
  }
}
