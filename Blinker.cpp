/* Blinker.cpp - Blink LEDs nicely
 *
 * Copyright (c) 2024 Márcio Pessoa
 *
 * Notice: This library is licensed under the MIT License.
 */

#include "Blinker.h"
#include "Arduino.h"

Blinker::Blinker(byte pin, unsigned int millis_period, bool state) {
  _pin = pin;
  _millis_period = millis_period;
  _state = state;
  _millis_elapsed = 0;
  _enable = true;
  _min = 0;
  _max = 255;
}

void Blinker::begin() {
  pinMode(_pin, OUTPUT);
}

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

bool Blinker::fade() {
  if (!_enable) {
    return false;
  }
  int brightness;
  float x;
  long millis_current = millis();
  // Build a linear x variable (0 ~ 1)
  x = (float)(millis_current - _millis_elapsed) / _millis_period;
  x *= M_PI;
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

bool Blinker::fadeLimits(int min, int max) {
  if (min < 0 || max > 255 || min >= max) {
    return true;
  }
  _min = min;
  _max = max;
  return false;
}

void Blinker::periodWrite(unsigned int millis_period) {
  _millis_period = millis_period;
}

unsigned int Blinker::periodRead() {
  return _millis_period;
}

void Blinker::off() {
  digitalWrite(_pin, LOW);
}

void Blinker::disable() {
  _enable = false;
  digitalWrite(_pin, LOW);
}

void Blinker::enable() {
  _enable = true;
}

bool Blinker::status() {
  return _enable;
}
