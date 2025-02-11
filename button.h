#ifndef button_h
#define button_h

class Button
{
  private:
    int buttonPins [8] = {6, 7, 8, 9, 10, 11, 12, 13};// Pins to read the buttons

    int buttonStates [8]; // checks which buttons are pressed

    int ledStates [8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};// LED states corresponding to associated button

    int lastButtonStates [8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};// for button debouncing

    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

    unsigned long debounceDelay = 50;    // the debounce time in milliseconds
  
  public:
    // Constructor
    Button();

    bool isCorrectButtonPressed = true;// Initially true until wrong button is pressed

    int correctButtonsPressed = 0;// used to check how many buttons have been pressed in the correct order  

    // Checks if any buttons have gone high 
    // and if the buttons are being pressed in the correct order.
    void pollButtons();

    void assignButtonPins(int* ledSequenceArray);

}; // end of class sequenceGenerator

#endif