#include "sequenceGenerator.h"
#include "button.h"

SequenceGenerator repeatSeqGen = SequenceGenerator( 2, 3, 4, 5, A2, A3, A4, A5);

void setup() {
  Serial.begin(9600);
  repeatSeqGen.pinSetup();
  repeatSeqGen.beginLevel();
  Serial.println("LEVEL: 1");
  delay(1000); 
  repeatSeqGen.sequence();
}


int level = 1;
Button buttons = Button();
void loop() {

if(level == 1) buttons.assignButtonPins(repeatSeqGen.ledSequenceArray);

buttons.pollButtons();
  if(buttons.isCorrectButtonPressed) 
  {
    if(buttons.correctButtonsPressed == 8)
    {
      if(level == 4)
     {// game is finished
     Serial.println("Congratulations!!! You win.");
      repeatSeqGen.gameFinishedSequence(level);
     }
      buttons.correctButtonsPressed = 0;
      repeatSeqGen.completedLevelSequence(); 
      buttons.isCorrectButtonPressed = true;// to run poll buttons again
      level++;
      repeatSeqGen.randomiseLedSequenceArray(level);
      repeatSeqGen.beginLevel(); 
      Serial.print("LEVEL: ");
      Serial.println(level);
      delay(1000);
      repeatSeqGen.sequence();
      buttons.assignButtonPins(repeatSeqGen.ledSequenceArray);
    }
  } else{
    Serial.println("Game Over :(");
    repeatSeqGen.resetSequence(buttons.isCorrectButtonPressed);
  }

}// void loop function
