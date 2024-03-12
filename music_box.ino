#include <Key.h>
#include <Keypad.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "pitches.h"

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {8, 7, 6, 5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

uint8_t pin = 4;
uint8_t led_pin = 2;
uint32_t current_note = 0;

struct Note;

struct {
  uint32_t tempo = 100;
  uint32_t whole = 4 * 60/tempo * 1000;
  uint32_t half = whole/2;
  uint32_t quarter = whole/4;
  uint32_t eight = whole/8;
  uint32_t sixteenth = whole/16;
} n;

struct {
  uint32_t tempo = 140;
  uint32_t whole = 4 * 60/tempo * 1000;
  uint32_t half = whole/2;
  uint32_t quarter = whole/4;
  uint32_t eight = whole/8;
  uint32_t sixteenth = whole/16;
} p;

struct Note {
  uint16_t frequency;
  uint32_t duration;
  uint8_t repetitions;
};

Note grace[] = {
  {NOTE_CS4, n.sixteenth/2, 1},
  {NOTE_E4, n.quarter*1.5, 1},
  {NOTE_GS4, n.eight, 1},
  {NOTE_FS4, n.sixteenth, 1},
  {NOTE_GS4, n.sixteenth, 1},
  {NOTE_FS4, n.sixteenth, 1},
  {NOTE_E4, n.sixteenth, 1},
  {NOTE_GS4, n.eight, 1},
  {NOTE_CS4, n.eight, 1},
  {NOTE_E4, n.eight, 1},
  {NOTE_FS4, n.eight, 1},
  {NOTE_FS4, n.eight, 1},
  {NOTE_GS4, n.eight, 1},
  {NOTE_GS4, n.eight, 1},
  {NOTE_GS3, n.eight, 1},
  {NOTE_GS3, n.eight, 1},
  {NOTE_CS4, n.eight, 1},
  {NOTE_CS4, n.quarter*1.5, 1},

  {NOTE_FS4, n.eight, 1},
  {NOTE_GS4, n.sixteenth, 1},
  {NOTE_FS4, n.sixteenth, 1},
  {NOTE_E4, n.sixteenth, 1},
  {NOTE_FS4, n.sixteenth, 1},
  {NOTE_E4, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_E4, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_B3, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_B3, n.sixteenth, 1},
  {NOTE_A3, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_B3, n.sixteenth, 1},
  {NOTE_A3, n.sixteenth, 1},
  {NOTE_GS3, n.sixteenth, 1},
  {NOTE_B3, n.sixteenth, 1},
  {NOTE_A3, n.sixteenth, 1},
  {NOTE_GS3, n.sixteenth, 1},
  {NOTE_FS3, n.sixteenth, 1},
  {NOTE_E3, n.sixteenth, 1},

  {NOTE_A3, n.quarter*1.5, 1},
  {NOTE_A3, n.eight, 1},
  {NOTE_GS3, n.sixteenth/3*2, 1},
  {NOTE_A3, n.sixteenth/3*2, 1},
  {NOTE_GS3, n.sixteenth/3*2, 1},
  {NOTE_FS3, n.eight, 1},
  {NOTE_GS3, n.eight, 1},
  {NOTE_FS3, n.eight, 1},
  {NOTE_FS3, n.eight, 1},
  {NOTE_E3, n.eight, 1},
  {NOTE_E3, n.eight, 1},
  {NOTE_FS3, n.eight, 1},
  {NOTE_FS3, n.sixteenth, 1},
  {NOTE_GS3, n.sixteenth, 1},
  {NOTE_FS3, n.eight, 1},
  {NOTE_E3, n.eight, 1},
  {NOTE_B2, n.eight, 1},
  {NOTE_CS3, n.whole, 1},

  {NOTE_B2, n.sixteenth, 1},
  {NOTE_CS3, n.sixteenth, 1},
  {NOTE_E3, n.sixteenth, 1},
  {NOTE_FS3, n.sixteenth, 1},
  {NOTE_GS3, n.sixteenth, 1},
  {NOTE_B3, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_E4, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_B3, n.sixteenth, 1},
  {NOTE_A3, n.sixteenth, 1},
  {NOTE_FS3, n.sixteenth, 1},

  {NOTE_A4, n.quarter*1.5, 1},
  {NOTE_A4, n.eight, 1},
  {NOTE_A4, n.eight, 1},
  {NOTE_GS4, n.sixteenth/3*2, 1},
  {NOTE_A4, n.sixteenth/3*2, 1},
  {NOTE_GS4, n.sixteenth/3*2, 1},
  {NOTE_FS4, n.eight, 1},
  {NOTE_E4, n.eight, 1},
  {NOTE_GS4, n.sixteenth, 1},
  {NOTE_FS4, n.sixteenth, 1},
  {NOTE_E4, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_FS4, n.sixteenth, 1},
  {NOTE_E4, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_E4, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_B3, n.sixteenth, 1},
  {NOTE_DS4, n.sixteenth, 1},
  {NOTE_CS4, n.sixteenth, 1},
  {NOTE_B3, n.sixteenth, 1},
  {NOTE_GS3, n.sixteenth, 1},
  {NOTE_CS4, n.quarter*1.5, 1},

  {NOTE_CS4, n.eight, 1},
  {NOTE_CS4, n.eight, 1},
  {NOTE_DS4, n.eight, 1},
  {NOTE_DS4, n.eight, 1},
  {NOTE_E4, n.eight, 1},
  {NOTE_E4, n.eight, 1},
  {NOTE_DS4, n.eight, 1},
  {NOTE_DS4, n.eight, 1},
  {NOTE_CS4, n.eight, 1},
  {NOTE_CS4, n.eight, 1},
  {NOTE_FS3, n.eight, 1},
  {NOTE_FS3, n.eight, 1},
  {NOTE_GS3, n.eight, 1},
  {NOTE_A3, n.whole, 1},
  {NOTE_GS3, n.half, 1},
  {NOTE_B2, n.half, 1},
  {NOTE_CS3, n.whole*1.9, 1}
};

Note in_your_face[] = {
  {NOTE_C3, p.eight, 4}, 
  {0, p.eight, 1},
  {NOTE_C3, p.eight, 6}, 
  {0, p.eight, 1},
  {NOTE_C3, p.eight, 2}, 
  {0, p.eight, 2},
  {NOTE_C3, p.eight, 4}, 
  {0, p.eight, 1},
  {NOTE_C3, p.eight, 1}, 
  {0, p.eight, 1},
  {NOTE_C3, p.eight, 1}, 
  {0, p.eight, 1},
  {NOTE_C3, p.eight, 5}, 
  {0, p.eight, 2}
};

void setup() {
  // put your setup code here, to run once:
//  srand(time(NULL));
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long ticks = millis();
  char key = keypad.getKey();

  if (key) {
    songPlay(key);
  }
/*
  if (key == '1') {
    playSong(in_your_face);
  }

  if (key == '2') {
    playSong(grace);
  }
*/
}

void playSong(Note song_name[]) {
  uint32_t previousMillis = millis();
  for (int i = 0; i < sizeof(song_name) / sizeof(Note); i++) {
    for (int j = 0; j < song_name[i].repetitions; j++) {
      playNote(pin, song_name[i].frequency, song_name[i].duration);
    }
  }
}

void songPlay(int option) {
  if (option == '*') {
    n.tempo = 100;
    for (int i = 0; i < sizeof(grace) / sizeof(Note); i++) {
      for (int j = 0; j < grace[i].repetitions; j++) {
        playNote(pin, grace[i].frequency, grace[i].duration);
      }
    }
  }
  if (option == '0') {
    for (int i = 0; i < sizeof(in_your_face) / sizeof(Note); i++) {
      for (int j = 0; j < in_your_face[i].repetitions; j++) {
        playNote(pin, in_your_face[i].frequency, in_your_face[i].duration);
      }
    }
    for (int i = 0; i < sizeof(in_your_face) / sizeof(Note); i++) {
      for (int j = 0; j < in_your_face[i].repetitions; j++) {
        playNote(pin, in_your_face[i].frequency, in_your_face[i].duration);
      }
    }
  }
}

void playNote(uint8_t pin, uint16_t frequency, uint32_t duration) {
  uint32_t actualDuration = duration * 0.9;
  
  if (frequency > 0) {
    digitalWrite(led_pin, HIGH);
    tone(pin, frequency, actualDuration);
  }
  delay(actualDuration);
  digitalWrite(led_pin, LOW);
  delay(duration - actualDuration);
}
