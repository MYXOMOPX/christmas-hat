#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "defs.cpp"

class LedMachine {
  Adafruit_NeoPixel* strip;
  int interval; 
  long startTime = 0;
  long lastTickTime = -50;
  int mode;
  int* modeParams;
  int ledCount = 0;
 
public: 
  bool loop = true;
  bool isRunning = false;
  LedMachine(int pin, int ledCount) {
    this->ledCount = ledCount;
    this->strip = new Adafruit_NeoPixel(ledCount, pin);
  }

  void begin(){
    strip->begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip->clear();
    strip->show();            // Turn OFF all pixels ASAP
    strip->setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  }
  
  
  ~LedMachine() {
  }

  void setData(int intrval, int mod, int params[PARAMS_LENGTH]) {
    interval = intrval;
    mode = mod;
    modeParams = params;
  }

  void start() {
    startTime = millis();
    isRunning = true;
  }

  void stop() {
    isRunning = false;  
  }
  int lastLed = -1;
  void tick() {
    if (!isRunning) return;
    unsigned long currentTime = millis();
    if (currentTime-lastTickTime < 25) return;
    lastTickTime = currentTime;
    long timeDif = currentTime-startTime;
    int step = timeDif/interval;
    double stage = ((double)(timeDif%interval))/((double)interval);
    int led = step%(this->ledCount);
    snake(step,stage);
  }

  void snake(int step, double stage){
    strip->clear();
    int sl = ledCount*stage;
    int r = modeParams[0];
    int g = modeParams[1];
    int b = modeParams[2];
    int snakeSize = modeParams[3];
    int snakeCount = modeParams[4];
    int firstPixelHue = (step*15)*(65536 / 90); // One cycle of color wheel over 90 frames
    for (int sc = 0; sc < snakeCount; sc++) {
      int startLed = sl+sc*ledCount/snakeCount;
      for (int i = 0; i < snakeSize; i++) {
        double mp = (double)(i+1)/(snakeSize+1);
        int led = (startLed+i)%ledCount;
        if (r == 0 && g == 0 && b == 0) {
          int      hue   = firstPixelHue + led * 65536L / ledCount;
          uint32_t color = strip->gamma32(strip->ColorHSV(hue)); // hue -> RGB  
          strip->setPixelColor(led, color);
        } else {
          strip->setPixelColor(led, r*mp, g*mp, b*mp);
        }
      } 
    }
    strip->show();
  }
};
