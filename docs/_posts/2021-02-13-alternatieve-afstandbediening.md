---
layout: post
title: "Alternatieve afstandbediening"
toc: true
---

# Inhoudstafel
* TOC
{:toc}

# Doel

Omdat het onbeleefd is om een telefoon tijdens een gesprek te gebruiken, is het gebruik van WiFi en de telefoon als afstandsbediening minder favorabel. Daarom gaan we nu op zoek naar een alternatieve afstandsbediening.

Functie van de afstandsbediening: aan- en uitschakelen van een motor en minimum twee verschillende "scènes" activeren of potentiometer op afstand (dus minimum 3 knoppen of 1 knop en 2 potentiometers of ...). Daarnaast moet de afstandsbediening compact en licht zijn.

# Mogelijke technologiën
Er zijn twee mogelijke technologiën voor een afstandsbediening: 
- Infrarood (IR)
- 433 MHz RF  

## Infrarood
![infrarood receiver en transmitter](https://images-na.ssl-images-amazon.com/images/I/61VsDzyD5DL._SX342_.jpg) 
Verzender links, ontvanger rechts.

De IR verzender (transmitter) is een LED die licht uitzendt in het infrarode spectrum. De IR ontvanger (receiver) bestaat uit een fotodiode die het licht ontvangt waarna het omgezet wordt in elektrische signalen.

![uitleg coderen en decoderen](https://www.circuitbasics.com/wp-content/uploads/2017/05/Arduino-IR-Remote-Receiver-Tutorial-IR-Signal-Modulation-1024x276.png)  

### Voordelen
- bestaande afstandsbediening is te gebruiken (bv. van beamer of TV) 
- goedkoop ([3,35 euro voor een ontvanger](https://www.conrad.be/p/iduino-1485322-infrarood-ontvanger-geschikt-voor-arduino-1485322?utm_campaign=&utm_content=&utm_medium=&utm_source=&utm_term=&vat=true)) 
- meerdere signalen te versturen via IR 

### Nadelen
- LoS (Line of Sight) nodig tussen afstandsbediening en ontvanger, IR transmitter en receiver moeten dus zichtbaar zijn.
- geen potentiometer te gebruiken (denk ik) 
- one way communication (geen nadeel voor dit project) 

## 433MHz RF
![433MHz receiver en transmitter](https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2015/05/433-Copy.jpg?w=450&quality=100&strip=all&ssl=1)  
Ontvanger links, verzender rechts.

433MHz wordt soms gebruikt om toestellen op afstand te bedienen. Het bestaat ook uit een verzender en ontvanger.

### Voordelen
- goedkoop ([1,75 euro voor een ontvanger en zender](https://www.hobbyelectronica.nl/product/433mhz-rf-ontvanger-zender-set/))
- geen LoS nodig, dus er mogen mensen tussen de afstandsbediening en motor staan
- kan meer data versturen (bijvoorbeeld tekst)
- kan ook data potentiometer versturen 

### Nadelen
- 2de arduino te programmeren (dus geen bestaande afstandbediening te gebruiken) maar is op het eerste zicht niet ingewikkeld)  
- one way communication (geen nadeel voor dit project) 

# Conclusie
Een voorlopige conclusie:

Aangezien je geen LoS nodig hebt en een potentiometer kan gebruiken gaat onze voorkeur momenteel naar het 433MHz-systeem. Het lijkt ons het meest flexibele systeem en het gemakkelijkst weg te werken in ons eindproduct. De afstandsbediening is eventueel te 3D-printen of in een kunststof te maken en de verzender, potentiometer en andere knoppen kunnen aan een [Arduino Nano](https://store.arduino.cc/arduino-nano). 

# TODO
- batterij / levensduur

# Bronnen
- [circuitbasics.com](https://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/) ook met uitleg om IR receiver te programmeren met Arduino 
- [circuitbasics.com afbeelding](https://www.circuitbasics.com/wp-content/uploads/2017/05/Arduino-IR-Remote-Receiver-Tutorial-IR-Signal-Modulation-1024x276.png) 
- [randomnerdtutorials.com](https://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/) 

