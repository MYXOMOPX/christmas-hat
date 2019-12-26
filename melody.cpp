#include "pitches.h"
#include "melody.h"

extern int melody_notes = 44;
extern int melody[] = {
  NOTE_E5, 0, NOTE_E5, 0, NOTE_E5, 0,
  NOTE_E5, 0, NOTE_E5, 0, NOTE_E5,0,
  NOTE_E5, 0, NOTE_G5, 0, NOTE_C5, 0, NOTE_D5, 0,
  NOTE_E5, 0,
  NOTE_F5, 0, NOTE_F5, 0, NOTE_F5, 0, NOTE_F5, 0,
  NOTE_F5, 0, NOTE_E5, 0, NOTE_E5, 0, NOTE_E5, 0, NOTE_E5, 0,
  NOTE_E5, 0, NOTE_D5, 0, NOTE_D5, 0, NOTE_E5, 0,
  NOTE_D5, 0, NOTE_G5, 0
};

extern int tempo[] = {
  8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8,
  2, 2,
  8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 16, 16,16, 16,
  8, 8, 8, 8, 8, 8,
  4, 4, 4, 4
};
// We wish you a merry Christmas
int wish_melody_notes = 30;
int wish_melody[] = {
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

int wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};

// Santa Claus is coming to town
int santa_melody_notes = 28;
int santa_melody[] = {
  NOTE_G4, 0,
  NOTE_E4, 0, NOTE_F4, 0, NOTE_G4, 0, NOTE_G4, NOTE_G4, 0,
  NOTE_A4, 0, NOTE_B4, 0, NOTE_C5, 0, NOTE_C5, NOTE_C5, 0,
  NOTE_E4, 0, NOTE_F4, 0, NOTE_G4, 0, NOTE_G4, NOTE_G4, 0,
  NOTE_A4, 0, NOTE_G4, 0, NOTE_F4, 0, NOTE_F4, 0,
  NOTE_E4, 0, NOTE_G4, 0, NOTE_C4, 0, NOTE_E4, 0,
  NOTE_D4, 0, NOTE_F4, 0, NOTE_B3, 0,
  NOTE_C4, 0
};

int santa_tempo[] = {
  8, 8,
  8, 8, 8, 8, 4, 4, 4, 4, 4, 4,
  8, 8, 8, 8, 4, 4, 4, 4, 4, 4,
  8, 8, 8, 8, 4, 4, 4, 4, 4, 4,
  8, 8, 8, 8, 4, 4, 2, 2,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 2, 2, 4, 4,
  1, 1
};
