#include "Arduino.h"
#include "button.h"

Button::Button()
{
  // Setting up buttons as inputs
  for(int i = 6; i < 14; i++) pinMode(i, INPUT);
}// Button constructor


void Button::pollButtons()
{
while(isCorrectButtonPressed)
{//while loop based on isCorrectButtonPressed state
 for(int i = 0; i < 8; i++)
 {// for loop to poll all 8 buttons
  int buttonRead = digitalRead(buttonPins[i]);
    if (buttonRead != lastButtonStates[i]) 
    {
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) 
    {
      if (buttonRead != buttonStates[i]) 
      {
       buttonStates[i] = buttonRead;
        if (buttonStates[i] == HIGH)
        {
          ledStates[i] = HIGH;
          int previousLedPinState;
          int currentLedPinState;

           if(buttonPins[i] < 10)
           {// if the current button in the buttonPin array is a digital Pin
             currentLedPinState = digitalRead(buttonPins[i] - 4);
           }else
           {// else the current button in the buttonPin array is an analog Pin
             currentLedPinState =  digitalRead(buttonPins[i] + 6 );
           }         
           if(buttonPins[i-1] < 10)
           {// if the previous button in the buttonPin array is a digital Pin
             if(i != 0) previousLedPinState = digitalRead(buttonPins[i-1] - 4);
           }else
           {// else the previous button in the buttonPin array is an analog Pin
             if(i != 0) previousLedPinState = digitalRead(buttonPins[i-1] + 6 );
           }
           if((previousLedPinState == HIGH) || (i == 0))
            {// if correct button pressed
             if(currentLedPinState == LOW)
              {
               isCorrectButtonPressed = true;
               correctButtonsPressed++;
                if(buttonPins[i] < 10 )
                 {// if current pin is a digital pin
                  digitalWrite(buttonPins[i] - 4, ledStates[i]);
                 }else{// else current pin is an analog pin
                  digitalWrite(buttonPins[i] + 6, ledStates[i]);  
                 }
              }
            }else{// else incorrect button pressed 
               isCorrectButtonPressed = false;
              }// else incorrect button pressed  

        }// if buttonStates[i] is HIGH after debouncing

      }// if the state of the button that has been read differs from the current button state

    }// if debounce delay time has elapsed
  lastButtonStates[i] = buttonRead;// store button state read for next iteration of main loop
 }// for loop to poll all 8 buttons
 if(correctButtonsPressed == 8) break;// break out of loop if all buttons have been pressed 

}//while loop based on isCorrectButtonPressed state

for(int i = 0; i < 8; i++)
{
  lastButtonStates[i] = LOW;
  ledStates[i] = LOW;
}

}// pollButtons function

void Button::assignButtonPins(int* ledSequenceArray)
{
    int temp = 0;
    for(int i = 0; i < 8; i++)
    {
           if(ledSequenceArray[i] < 6 )
            {
              for(int j = 0; j < 8; j++ )
              {
                if(buttonPins[j] == (ledSequenceArray[i] + 4))
                { ///swap position of correct button Pin and current button Pin position
                  temp = buttonPins[j];
                  buttonPins[j] = buttonPins[i];
                  buttonPins[i] = temp;
                }// placing buttonPins in the same sequence as the ledSequenceArray
              }
            }// if digital pins 
           else
            {
             for(int j = 0; j < 8; j++ )
              {
                if(buttonPins[j] == (ledSequenceArray[i] - 6))
                { ///swap position of correct button Pin and current button Pin position
                  temp = buttonPins[j];
                  buttonPins[j] = buttonPins[i];
                  buttonPins[i] = temp;
                }// placing buttonPins in the same sequence as the ledSequenceArray
              }
            }// else analog pins
    }//for loop to place buttonPins members in the same order as the corresponding ledSequenceArray members
}