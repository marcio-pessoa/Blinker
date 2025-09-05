/* Blinker.h - Blink LEDs nicely
 *
 * Copyright (c) 2024 Márcio Pessoa
 *
 * Notice: This library is licensed under the MIT License.
 */

#ifndef Blinker_h
#define Blinker_h

#include "Arduino.h"
#include <math.h>

class Blinker {
 public:
  Blinker(byte pin, unsigned int millis_period = 1000, bool state = false);
  void begin();
  bool blink();
  bool fade();
  bool fadeLimits(int min, int max);
  void disable();
  void enable();
  bool status();
  void periodWrite(unsigned int millis_period);
  unsigned int periodRead();
  void off();

 private:
  byte _pin;
  unsigned int _millis_period;
  bool _state;
  bool _enable;
  unsigned long _millis_elapsed;
  unsigned int _min;
  unsigned int _max;
};

#endif
