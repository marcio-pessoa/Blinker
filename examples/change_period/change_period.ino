#include <RealTime.h>

int period = 1000;
Blinker led(13, period);

void setup() {
}

void loop() {
  led.blink();
  if (millis() % 1000 == 0) {
    period -= 1; //Decrease period
    led.change_period(period);
  }
}
