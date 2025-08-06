/* Blinker.h - Blink LEDs nicely
 *
 * Author: Márcio Pessoa <marcio.pessoa@gmail.com>
 * Contributors: none
 *
 * Change log
 * 2015-01-10
 *         * Blinker
 *         added default value to millis_period variable (1 second).
 *
 * 2014-11-17
 *         *
 *         Variable optimization: int _pin to byte _pin.
 *
 * 2014-10-28
 *         * blink
 *         code optimization.
 *
 * 2014-09-12
 *         * fade
 *         added fade method.
 *         * fadeLimits
 *         added fadeLimits method.
 *
 * 2014-08-04
 *         Experimental version.
 */

#ifndef Blinker_h
#define Blinker_h

#include "Arduino.h"

// If PI constant is not defined, plese uncoment the follow line:
// const float PI
// = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

class Blinker {
 public:
  Blinker(byte pin, unsigned int millis_period = 1000, bool state = false);
  bool blink();
  bool fade();
  bool fadeLimits(int min, int max);
  void disable();
  void enable();
  bool status();
  void periodWrite(unsigned int millis_period);
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
