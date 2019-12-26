#include "Arduino.h"

class StateButton {
  public:
    int value = 0; // current value
    int isChanged = 0; // Is val chagned on current handle tick
    
    StateButton(int pin, int debounceTime){
      this->pin = pin;
      this->debounce = debounceTime;
    }
    StateButton(int pin){
      this->pin = pin;
    }
    void begin(){
      pinMode(pin, INPUT_PULLUP);
    }
    
    void handle(){
        this->isChanged = 0; 
        int readedVal = digitalRead(pin);
        int prevReadedVal = this->prevReadedVal;
        this->prevReadedVal = readedVal;
        if (readedVal != prevReadedVal) {
            this->lastChangeMillis = millis();
            return;
        }
        if (millis() - this->lastChangeMillis < this->debounce) return;

        if (this->value != readedVal) this->isChanged = 1; 
        this->value = readedVal;
    }
  private:
    // Settings
    int pin;  
    int debounce = 50;

    // Vars for debounce
    int prevReadedVal = 0;
    long lastChangeMillis = 0;
};
