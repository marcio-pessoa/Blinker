/* Blinker.cpp - Blink LEDs nicely
 *
 * Copyright 2019-2020 Marcio Pessoa
 *
 */

#include "Blinker.h"
#include "Arduino.h"

/* Blinker
 *
 * Description
 *   Blink LED without delay function.
 *
 *   RealTime (int pin, int millis_period, boolean state)
 *
 * Parameters
 *   pin: Arduino LED pin
 *   millis_period: Time period to define blink delay (milliseconds)
 *   state: Initial LED state
 *
 * Returns
 *   void
 */
Blinker::Blinker(byte pin, unsigned int millis_period, bool state) {
  pinMode(pin, OUTPUT);
  _pin = pin;
  _millis_period = millis_period;
  _state = state;
  _millis_elapsed = 0;
  _enable = true;
  _min = 0;
  _max = 255;
}

/* blink
 *
 * Description
 *   Blink LED when time period expires.
 *
 *   a_led.blink()
 *
 * Parameters
 *   none
 *
 * Returns
 *   false: if the last state was not modified
 *   true: if the last state was modified
 */
bool Blinker::blink() {
  if (!_enable) {
    return false;
  }
  long millis_current = millis();
  if (millis_current - _millis_elapsed >= (_millis_period / 2)) {
    digitalWrite(_pin, _state);
    _millis_elapsed = millis_current;
    _state = !_state;
    return true;
  }
  return false;
}

/* fade
 *
 * Description
 *   Fade LED nicely.
 *
 *   a_led.fade()
 *
 * Parameters
 *   void
 *
 * Returns
 *   false: if the last state was not modified
 *   true: if the last state was modified
 */
bool Blinker::fade() {
  if (!_enable) {
    return false;
  }
  int brightness;
  float x;
  long millis_current = millis();
  // Build a linear x variable (0 ~ 1)
  x = (float)(millis_current - _millis_elapsed) / _millis_period;
  x *= PI;
  // Apply cos function to brightness
  brightness = (((-cos(x * 2)) + 1) / 2 * (_max - _min)) + _min;
  analogWrite(_pin, brightness);
  // Reset timer
  if (millis_current - _millis_elapsed >= _millis_period) {
    _millis_elapsed = millis_current;
    _state = !_state;
    return true;
  }
  return false;
}

/* fadeLimits
 *
 * Description
 *   Define fade limits.
 *
 *   a_led.fadeLimits()
 *
 * Parameters
 *   int min
 *   int max
 *
 * Returns
 *   false: if no error
 *   true: if error found
 */
bool Blinker::fadeLimits(int min, int max) {
  if (max <= min or max > 255 or max < 1 or min < 0 or min > 254) {
    return true;
  }
  _min = min;
  _max = max;
  return false;
}

/* periodWrite
 *
 * Description
 *   Change period used to blink LED.
 *
 *   a_led.periodWrite(int millis_period)
 *
 * Parameters
 *   millis_period: Time period to define blink delay (milliseconds)
 *
 * Returns
 *   void
 */
void Blinker::periodWrite(unsigned int millis_period) {
  _millis_period = millis_period;
}

void Blinker::off() { digitalWrite(_pin, LOW); }

/* disable
 *
 * Description
 *   Disable LED to blink.
 *
 *   a_led.stop()
 *
 * Parameters
 *   none
 *
 * Returns
 *   void
 */
void Blinker::disable() {
  _enable = false;
  digitalWrite(_pin, LOW);
}

/* enable
 *
 * Description
 *   Enable LED to blink.
 *
 *   a_led.start()
 *
 * Parameters
 *   none
 *
 * Returns
 *   void
 */
void Blinker::enable() { _enable = true; }

/* status
 *
 * Description
 *   Return LED status.
 *
 *   a_led.status(int millis_period)
 *
 * Parameters
 *   none
 *
 * Returns
 *   bool: false if LED is not blinking, true if LED is blinking
 */
bool Blinker::status() { return _enable; }
