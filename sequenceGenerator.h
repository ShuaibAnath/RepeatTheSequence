#ifndef sequenceGenerator_h
#define sequenceGenerator_h

class SequenceGenerator
{
  private:
  int diode1;
  int diode2;
  int diode3;
  int diode4;
  int diode5;
  int diode6;
  int diode7;
  int diode8;

  public:

     int ledSequenceArray [8] = {2, 3, 4, 5, A2, A3, A4, A5};// array that determines the sequence of LED lighting 
  
     SequenceGenerator(int led1, int led2, int led3, int led4, int led5, int led6, int led7, int led8); // begin level sequence of lighting
     
     void pinSetup();//Set LED pins to output

     void beginLevel();//LED lighting arrangement for the beginning of a level 

     void randomiseLedSequenceArray (int &level);//generates array for random positions

    // Populates ledSequenceArray with pin numbers connected to the LEDs (randomly, by index)
     void populateLedSequenceArray(int &arrayMembersLeft, int numberOfMembersToInsert, int arrayPins[], int &i, int minRandNumber, int maxRandNumber);

     //Generates a sequence
     void sequence();

     void resetSequence(bool &isCorrectButtonPressed);

     void completedLevelSequence();

     void gameFinishedSequence(int &level);
     
}; // end of class sequenceGenerator

#endif