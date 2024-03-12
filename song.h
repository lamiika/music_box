#include "pitches.h"

struct Note;

struct {
  uint32_t tempo = 140;
  uint32_t whole = 4 * 60/tempo * 1000;
  uint32_t half = whole/2;
  uint32_t quarter = whole/4;
  uint32_t eight = whole/8;
  uint32_t sixteenth = whole/16;
} n;

struct Note {
  uint16_t frequency;
  uint32_t duration;
  uint8_t repetitions;
};

#define Note notes[] = {
  {NOTE_C2, n.eight, 4}, 
  {0, n.eight, 1},
  {NOTE_C2, n.eight, 6}, 
  {0, n.eight, 1},
  {NOTE_C2, n.eight, 2}, 
  {0, n.eight, 2},
  {NOTE_C2, n.eight, 4}, 
  {0, n.eight, 1},
  {NOTE_C2, n.eight, 1}, 
  {0, n.eight, 1},
  {NOTE_C2, n.eight, 1}, 
  {0, n.eight, 1},
  {NOTE_C2, n.eight, 5}, 
  {0, n.eight, 2}
};