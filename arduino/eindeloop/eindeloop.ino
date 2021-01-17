
const int IN_PIN =  21; 

// maak variabele aan voor status shakelaar
char eindschakelStatus = 0;

// this setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin as input or output
  pinMode(IN_PIN, INPUT);
  Serial.begin(9600);
}

// this loop function runs over and over again forever
void loop() 
{
  // read the state of the input pin :
  eindschakelStatus = digitalRead(IN_PIN);

  // if the input pin is high
  if (eindschakelStatus == HIGH) {
    // turn LED on:
    Serial.println("aan");
  }
  else { // if the input pin is low
    // turn LED off:
    Serial.println("uit");
 }
}
