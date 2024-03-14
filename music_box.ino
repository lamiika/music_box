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

  if (key) {
    songPlay(key);
  }
/*
  if (key == '1') {
    setTempo(140);
    playSong(in_your_face);
  }

  if (key == '2') {
    setTempo(100);
    playSong(grace);
  }
*/
}

void setTempo(uint32_t value) {
  whole_note = 4*60/value*1000;
}

void playSong(Note song_name[]) {
  uint32_t previousMillis = millis();
  for (int i = 0; i < sizeof(song_name) / sizeof(Note); i++) {
    for (int j = 0; j < song_name[i].repetitions; j++) {
      playNote(pin, song_name[i].frequency, song_name[i].division);
    }
  }
}

void songPlay(int option) {
  if (option == '*') {
    setTempo(100);
    for (int i = 0; i < sizeof(grace) / sizeof(Note); i++) {
      for (int j = 0; j < grace[i].repetitions; j++) {
        playNote(pin, grace[i].frequency, grace[i].division);
      }
    }
  }
  if (option == '0') {
    setTempo(140);
    for (int i = 0; i < sizeof(in_your_face) / sizeof(Note); i++) {
      for (int j = 0; j < in_your_face[i].repetitions; j++) {
        playNote(pin, in_your_face[i].frequency, in_your_face[i].division);
      }
    }
    for (int i = 0; i < sizeof(in_your_face) / sizeof(Note); i++) {
      for (int j = 0; j < in_your_face[i].repetitions; j++) {
        playNote(pin, in_your_face[i].frequency, in_your_face[i].division);
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
