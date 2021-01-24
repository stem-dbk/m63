
const int eind1 = 21;   // pin van input eerste eindeloopschakelaar
const int eind2 = 22;   // pin van input tweede eindeloopschakelaar

// maak variabele aan voor status shakelaars
char eind1Status = 0;
char eind2Status = 0;

// this setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin as input or output
  pinMode(eind1, INPUT);
  pinMode(eind2, INPUT);
  Serial.begin(9600);
}

// this loop function runs over and over again forever
void loop() 
{
  // read the state of the input pin :
  eind1Status = digitalRead(eind1);
  eind2Status = digitalRead(eind2);

  // als de input van 1 HIGH is
  if (eind1Status == HIGH) {
    Serial.println("eind 1 aan");   // toon op scherm ..
  }

  if (eind2Status == HIGH) {
    Serial.println("eind 2 aan");
  }
  
}
