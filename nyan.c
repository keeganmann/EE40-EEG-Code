#include <avr/io.h>
#define F_CPU 1000000UL  // 1 MHz
#include <util/delay.h>
#include "nyandata.h"


void tone(uint16_t note,uint8_t duration){
  OCR0A = 1000000/8/note;
  if(duration == 8){
    _delay_ms(1000/8.0);
    TCCR0B &= ~(_BV(CS01));
    _delay_ms(1000/8.0);
    TCCR0B |= (_BV(CS01));
  }
  else{//16
    _delay_ms(1000/16.0);
    TCCR0B &= ~(_BV(CS01));
    _delay_ms(1000/16.0);
    TCCR0B |= (_BV(CS01));
  }
}

void setup() {
  uint8_t thisNote;
  for ( thisNote = 0; thisNote < 25; thisNote++) {
    tone(intro[thisNote],noteDurations[thisNote]);
  }
}

void loop() {
  uint8_t thisNote;
  for (thisNote = 0; thisNote < 216; thisNote++) {
    tone(melody[thisNote],melodyNoteDurations[thisNote]);
  }
}
