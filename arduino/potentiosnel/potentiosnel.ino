
// een functie voor aanpasbare snelheid
int potentio(){
  int potentioVal = analogRead(potentioSen);
  int rangeVal = 512/35;
  if(potentioVal < 512){
    snelOmlaag = 35 - (-(potentioVal-512)/rangeVal);
    snelOmhoog = 150 - (-(potentioVal-512)/rangeVal);
  } else if (potentioVal > 512){
    snelOmlaag = 35 + (potentioVal-512)/rangeVal;
    snelOmhoog = 150 + (-(potentioVal-512)/rangeVal);
  } else if(potentioVal = 512){
    snelOmlaag = 35;
    snelOmhoog = 150;
  }
}
