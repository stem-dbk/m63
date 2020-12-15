// een naam aan de pinnen geven (variabelen), om het programma overzichtelijk te houden
int SENSOR_PIN = 18; // Arduino analog input pin 18 = A18; middelste pinnetje
 
int RPWM_Output = 5; // Arduino PWM output pin 5; geconnecteerd met pin 1 van de H-brug (RPWM) Forward level
int LPWM_Output = 6; // Arduino PWM output pin 6; geconnecteerd met pin 2 van de H-brug (LPWM) Reverse Level
 
// eerste wat het programma eenmalig doet
void setup() {
  
  // we zeggen aan de brainbox (Arduino) dat de twee PWM-pinnen output zijn (analoog), omdat je iets verstuurt
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
  
}

// dit wordt herhaald
void loop()
{
  int sensorValue = analogRead(SENSOR_PIN); // we maken een variabele aan voor de functie om de potentiometer analoog uit te lezen
 
  // sensor geeft waardes tussen 0 tot en met 1023
  // de eerste helft gebruiken we om achteruit de draaien; de tweede helft om vooruit te draaien

  // ! er is nog iets vreemds met het uitlezen van de sensor !
  // waarde van de sensor uilezen om te achterhalen wat er niet werkt
  Serial.print(sensorValue);
  
  if (sensorValue < 512)   // als uitgelezen waarde kleiner is dan 512 dan moet hij achteruit
  {
    int reversePWM = -(sensorValue - 511) / 2;   // waarde voor de snelheid van de PWM instellen (tussen 0 en 255)
    analogWrite(LPWM_Output, 0);  // Reverse level moet op 0 = stilstaan
    analogWrite(RPWM_Output, reversePWM);   // aan Forward level geven de waarde van de sensor gedeeld door twee
  }
  else // als uitgelezen waarde hoger of gelijk is aan 512, moet hij vooruit
  {
    int forwardPWM = (sensorValue - 512) / 2; //forwardPWM contains the forward PWMspeed between 0 and 255
    analogWrite(LPWM_Output, forwardPWM); // aan Reverse level geven de waarde van de sensor gedeeld door twee
    analogWrite(RPWM_Output, 0); // Forward level moet op 0 = stilstaan
  }
}
