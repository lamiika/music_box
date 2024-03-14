#include "song.h"
#include "keypad.h"

#include "pitches.h"

uint8_t pin = 4;
uint8_t led_pin = 2;
uint32_t whole_note = 4*60/100*1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long ticks = millis();
  char key = keypad.getKey();

  switch(key) {
    size_t song_length;
    case '1':
      song_length = sizeof(in_your_face) / sizeof(Note);
      playSong(in_your_face, song_length);
      break;
    case '2':
      song_length = sizeof(grace) / sizeof(Note);
      playSong(grace, song_length);
      break;
    default:
      break;
  }
}

void setTempo(uint32_t value) {
  whole_note = 4*60/value*1000;
}

void playSong(Note song_name[], size_t song_length) {
  uint32_t previousMillis = millis();
  setTempo(song_name[0].frequency);
  uint16_t repetitions = song_name[0].repetitions;

  for (int times_played = 0; times_played < repetitions; times_played++) {
    for (int note_index = 1; note_index < song_length; note_index++) {
      // 0 index used for metadata ^
      for (int repeat_note = 0; repeat_note < song_name[note_index].repetitions; repeat_note++) {
        playNote(pin, song_name[note_index].frequency, song_name[note_index].division);
      }
    }
  }
}

void playNote(uint8_t pin, uint16_t frequency, float division) {
  uint32_t duration = whole_note / division;

  uint32_t actualDuration = duration * 0.9;
  
  if (frequency > 0) {
    digitalWrite(led_pin, HIGH);
    tone(pin, frequency, actualDuration);
  }
  delay(actualDuration);
  digitalWrite(led_pin, LOW);
  delay(duration - actualDuration);
}
