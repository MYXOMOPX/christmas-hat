#include <Arduino.h>


#define NOTES_COUNT 203

class MusicMachine {
  int pin = -1;
  int length = 0;
  int lastNoteIndex = -1;
  long startTime = 0;
  int* notes;
  int* duration;
  int notes_count;
  double speed;
 
public: 
  bool loop = false;
  bool isRunning = false;
  MusicMachine(int pin) {
    this->pin = pin;
  }

  void begin(){
  }
  
  
  ~MusicMachine() {
  }

  void start() {
    startTime = millis();
    isRunning = true;
  }

  void setData(int nts[], int durs[], int cnt, double spd) {
    notes = nts;
    duration = durs;
    notes_count = cnt;
    speed = spd;
  }

  void stop() {
    isRunning = false;  
  }
  
  void tick() {
    if (!isRunning) return;
    long currentTime = millis();
    long timeDif = currentTime-this->startTime;
    int noteIndex = -1;
    long timeSum = 0;
    while (timeDif > timeSum) {
      noteIndex++;
      if (noteIndex >= notes_count) {
        if (this->loop) {
          this->startTime = millis();
          this->lastNoteIndex = -1;  
        } else {
          isRunning = false;  
        }
        return;
      };
      timeSum += 1000/duration[noteIndex]*speed;  
    }
    if (noteIndex == -1) return;
    if (noteIndex == lastNoteIndex || noteIndex >= notes_count) return;
    lastNoteIndex = noteIndex;
    int timeLeft = 1000/duration[noteIndex]*speed-(timeDif-timeSum);
    tone(pin,notes[noteIndex],timeLeft);
  }
};
