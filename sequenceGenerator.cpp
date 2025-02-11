#include "Arduino.h" 
#include "sequenceGenerator.h"

  SequenceGenerator::SequenceGenerator(int led1, int led2, int led3, int led4, int led5, int led6, int led7, int led8)
  {
    diode1 = led1;
    diode2 = led2;
    diode3 = led3;
    diode4 = led4;
    diode5 = led5;
    diode6 = led6;
    diode7 = led7;
    diode8 = led8;
  }// SequenceGenerator constructor

  void SequenceGenerator::pinSetup()
  {
   pinMode(diode1, OUTPUT);
   pinMode(diode2, OUTPUT);
   pinMode(diode3, OUTPUT);
   pinMode(diode4, OUTPUT);
   pinMode(diode5, OUTPUT);
   pinMode(diode6, OUTPUT);
   pinMode(diode7, OUTPUT);
   pinMode(diode8, OUTPUT);
  }// setting of LED pins to OUTPUT


  void SequenceGenerator::beginLevel()
  {
   // All LEDs are lit to indicate a level will begin.

   for(int i = 2; i < 6; i++) digitalWrite(i, HIGH);// write to digital pins

   for(int i = 16; i < 20; i++) digitalWrite(i, HIGH);// write to analog pins
   delay(5000);

   for(int i = 2; i < 6; i++) digitalWrite(i, LOW);// write to digital pins

   for(int i = 16; i < 20; i++) digitalWrite(i, LOW); // write to analog pins
   delay(2000);// wait 2 seconds before starting level

  }// begin level for lighting LEDS


  void SequenceGenerator::sequence()
  {
    for(int i = 0; i < 8; i++)
    {// loop that lightathe LEDs in the sequence of the pins given by the array "ledSequenceArray" 
      digitalWrite(ledSequenceArray[i], HIGH); // 
      delay(2000);// wait 2 seconds before lighting next LED
    }// write to digital pins

    for(int i = 2; i < 6; i++) digitalWrite(i, LOW);// write to digital pins

    for(int i = 16; i < 20; i++) digitalWrite(i, LOW); // write to analog pins

  }// sequence of LED lighting


void SequenceGenerator::resetSequence(bool &isCorrectButtonPressed)
{
  while(!isCorrectButtonPressed)
  {
   for(int i = 2; i < 6; i++) digitalWrite(i, HIGH); // write to digital pins
   delay(500);

   for(int i = 2; i < 6; i++) digitalWrite(i, LOW);// write to digital pins 
   delay(500);

   for(int i = 16; i < 20; i++)digitalWrite(i, HIGH);// write to analog pins
   delay(500);

   for(int i = 16; i < 20; i++)digitalWrite(i, LOW);// write to analog pins
   delay(500);
  }
}//resetSequence


void SequenceGenerator::completedLevelSequence()
{
  // Turn off all LEDs
  for(int i = 2; i < 6; i++) digitalWrite(i, LOW);// write to digital pins 

  for(int i = 16; i < 20; i++) digitalWrite(i, LOW); // write to analog pins

  for(int i = 2; i < 6; i++){
    digitalWrite(i, HIGH);
    delay(200);
   }// write to digital pins

    for(int i = 6; i > 1 ; i--){
      digitalWrite(i, LOW);
      delay(200);
   }// write to digital pins 
    
   for(int i = 20; i > 15; i--){
     digitalWrite(i, HIGH);
     delay(200);
   }// write to analog pins
    
    for(int i = 16; i < 20; i++){
     digitalWrite(i, LOW);
     delay(200);
   }// write to analog pins
  
}//completed level sequence


void SequenceGenerator::randomiseLedSequenceArray (int &level)
{ 
  int arrayMembersLeft = 8;
  int i = 0;
  
  for(int j = 0; j < 8; j++)  ledSequenceArray[j] = 0;// for loop to reset led Sequence array

  if(level == 2)
  {// level 2
   int arrayDigitalPins1 [2] = {2, 3};
   int arrayDigitalPins2 [2] = {4, 5};
   int arrayAnalogPins1 [2] = {A2, A3};
   int arrayAnalogPins2 [2] = {A4, A5};

   populateLedSequenceArray(arrayMembersLeft,  (arrayMembersLeft - 2), arrayDigitalPins1, i, 0, 2);
   i = 0;
   populateLedSequenceArray(arrayMembersLeft,  (arrayMembersLeft - 2), arrayDigitalPins2, i, 2, 4);
   i = 0;
   populateLedSequenceArray(arrayMembersLeft,  (arrayMembersLeft - 2), arrayAnalogPins1, i, 4, 6);
   i = 0;
   populateLedSequenceArray(arrayMembersLeft,  (arrayMembersLeft - 2), arrayAnalogPins2, i, 6, 8);
  }// level 2

  if(level == 3)
  {// level 3
   int arrayDigitalPins [4] = {2, 3, 4, 5};
   int arrayAnalogPins [4] = {A2, A3, A4, A5};

   populateLedSequenceArray(arrayMembersLeft,  (arrayMembersLeft - 4), arrayDigitalPins, i, 0, 4);
   i = 0;
   populateLedSequenceArray(arrayMembersLeft,  (arrayMembersLeft - 4), arrayAnalogPins, i, 4, 8);
  }// level 3

  if(level == 4)
  {//level 4
  int arrayLevel4Pins [8] = {2, 3, 4, 5, A2, A3, A4, A5};
  populateLedSequenceArray(arrayMembersLeft,  (arrayMembersLeft - 4), arrayLevel4Pins, i, 0, 8);
  populateLedSequenceArray(arrayMembersLeft,  (arrayMembersLeft - 4), arrayLevel4Pins, i, 0, 8);
  }//level 4

}//generateRandomArray


void SequenceGenerator::populateLedSequenceArray(int &arrayMembersLeft, int numberOfMembersToInsert, int arrayPins[], int &i, int minRandNumber, int maxRandNumber)
{
  randomSeed(analogRead(0));
  int randomIndex = random(minRandNumber, maxRandNumber);
  while(arrayMembersLeft > numberOfMembersToInsert)
  {// place pin numbers in random positions of ledSequenceArray
      if(ledSequenceArray[randomIndex] == 0)
      {
        ledSequenceArray[randomIndex] = arrayPins[i];
        i++;
        arrayMembersLeft--;
      }
   randomIndex = random(minRandNumber, maxRandNumber);
  }
}//populate ledSequenceArray


void SequenceGenerator::gameFinishedSequence(int &level)
 {
   while(level == 4)
   { 
    for(int i = 2; i < 6; i++) digitalWrite(i, HIGH); // write to digital pins
    for(int i = 16; i < 20; i++)digitalWrite(i, HIGH);// write to analog pins
    delay(500);

    for(int i = 2; i < 6; i++) digitalWrite(i, LOW);// write to digital pins 
    for(int i = 16; i < 20; i++)digitalWrite(i, LOW);// write to analog pins
    delay(500);
   }//while level == 4
 }//gameFinishedSequence