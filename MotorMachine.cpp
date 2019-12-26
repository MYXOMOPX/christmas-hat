#include <Adafruit_TiCoServo.h>
#include <Arduino.h>

class MotorMachine {
  Adafruit_TiCoServo* servo = new Adafruit_TiCoServo();
  int pin = -1;
  int* angles;
  int* intervals; 
  int lastStep = -1;
  long startTime = 0;
  int length = 0;
 
public: 
  bool loop = true;
  bool isRunning = false;
  MotorMachine(int pin) {
    this->pin = pin;
  }

  void begin(){
    servo->attach(pin, 700, 2700);
  }
  
  
  ~MotorMachine() {
    servo->detach();
  }

  void setData(int* angles, int* intervals, int length) {
    this->angles = angles;
    this->intervals = intervals;
    this->length = length;
  }

  void start() {
    startTime = millis();
    isRunning = true;
  }

  void stop() {
    isRunning = false;  
  }
  
  void tick() {
    if (!isRunning) return;
    long currentTime = millis();
    long timeDif = currentTime-this->startTime;
    int currentStep = -1;
    long timeSum = 0;
    while (timeDif > timeSum) {
      currentStep++;
      if (currentStep >= this->length) {
        if (this->loop) {
          this->startTime = millis();
          this->lastStep = -1; 
        } else {
          isRunning = false;  
        }
        return;
      };
      timeSum += this->intervals[currentStep];  
    }
    if (currentStep == -1) return;
    if (currentStep == lastStep || currentStep > this->length-1) return;
    lastStep = currentStep;
    Serial.print("Motor ");
    Serial.println(this->angles[currentStep]);
    servo->write(this->angles[currentStep]);
  }
};
