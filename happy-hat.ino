#include <Arduino.h>
#include "defs.cpp"
#include "MotorMachine.cpp"
#include "LedMachine.cpp"
#include "MusicMachine.cpp"
#include "StateButton.cpp"
#include "melody.h"

MotorMachine mm(PIN_SERVO);
LedMachine lm(PIN_WS2812,LED_COUNT);
MusicMachine mus(PIN_BUZZER);
StateButton btnTilt(PIN_TILT);
StateButton btnLedParams(PIN_BTN_LED_TYPE);
StateButton btnLedMods(PIN_BTN_LED_MOD);
StateButton btnServo(PIN_BTN_SERVO);


#define MODE_COUNT 2
int currentLedMode = 0;
int currentLedParams = 0;
int LED_MODE_SNAKE[][PARAMS_LENGTH] = {
    {255,0,0,4,1,0}, {0,255,0,4,1,0}, {0,0,255,4,1,0},
    {255,0,255,4,1,0}, {0,255,255,4,1,0}, {255,255,0,4,1,0},
    {255,255,255,4,1,0}, {0,0,0,4,1,0}
};
int LED_MODE_DOUBLE_SNAKE[][PARAMS_LENGTH] = {
    {255,0,0,4,2,0}, {0,255,0,4,2,0}, {0,0,255,4,2,0},
    {255,0,255,4,2,0}, {0,255,255,4,2,0}, {255,255,0,4,2,0},
    {255,255,255,4,2,0}, {0,0,0,4,2,0}
};

//////////////////////////////////////////
int motor_angles[] = {
  0,130,0,130,0,130,0,130,0,130,0,130,0,130,0,130
};
int motor_times[] = {
  500,2000,
  700,1500,
  650,1700,
  300,1400,
  300,1400,
  300,1400,
  500,1000,
  250,300
};
////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hi there");
  mm.setData((int*)motor_angles, (int*)motor_times, 16);
  mm.loop = true;
  mm.begin();
  //mm.start();

  updateStripModeAndParams();
  lm.begin();
  // lm.start();

  //mus.setData((int*)santa_melody,(int*)santa_tempo,santa_melody_notes,1.5);
  //mus.start();

  btnLedMods.begin();
  btnLedParams.begin();
  btnTilt.begin();
  btnServo.begin();
}
bool shakeWithMusic = false; 
void loop() {
  btnTilt.handle();
  btnLedParams.handle();
  btnLedMods.handle();
  btnServo.handle();
  if (btnTilt.isChanged && btnTilt.value == LOW) {
      shakeWithMusic = true;
      mm.start(); 
      mm.loop = true;
      startRandomMusic();
  }
  if (btnServo.isChanged && btnServo.value == LOW) {
      mus.stop();
      shakeWithMusic = false;
      if (mm.isRunning) {
        mm.stop();  
      } else {
        mm.start(); 
        mm.loop = true;
      }
  }
  if (btnLedParams.isChanged && btnLedParams.value == HIGH) {
      handleChangeParams();
      updateStripModeAndParams();
  }
  if (btnLedMods.isChanged && btnLedMods.value == HIGH) {
      handleChangeMode();
      updateStripModeAndParams();
  }
  if (!mus.isRunning && shakeWithMusic) {
      mm.stop();  
  }
  mm.tick();
  lm.tick();
  mus.tick();
}

void handleChangeMode(){
  currentLedMode = (currentLedMode+1)%MODE_COUNT;
  currentLedParams = 0;
  Serial.println("MODE++");
}

void handleChangeParams(){
  currentLedParams++;
}

void updateStripModeAndParams(){
  int paramsCount;
  switch (currentLedMode) {
    case 0: 
      paramsCount = sizeof(LED_MODE_SNAKE)/sizeof(*LED_MODE_SNAKE);
      lm.setData(2000,0,LED_MODE_SNAKE[currentLedParams%paramsCount]);
      break;
    case 1: 
      paramsCount = sizeof(LED_MODE_DOUBLE_SNAKE)/sizeof(*LED_MODE_DOUBLE_SNAKE);
      lm.setData(2000,0,LED_MODE_DOUBLE_SNAKE[currentLedParams%paramsCount]);
      break;
  }
  lm.start();
}

void startRandomMusic(){
  double speed = 1.3;
  int rnd = random(0, 5);
  if (rnd < 3) {
    mus.setData((int*)wish_melody,(int*)wish_tempo,wish_melody_notes,speed);
    mus.start();
  } else if (rnd < 5) {
    mus.setData((int*)melody,(int*)tempo,melody_notes,speed);
    mus.start();
  } else {
    mus.setData((int*)santa_melody,(int*)santa_tempo,santa_melody_notes,speed);
    mus.start();
  }
}
