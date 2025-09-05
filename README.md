# Arduino Blinker Library

An Arduino library for blinking and fading LEDs without using `delay()`, which allows your `loop()` to run without being blocked. This library is lightweight, easy to use, and supports all Arduino boards.

## Features

- Blink an LED with a specified period.
- Fade an LED in and out smoothly using a cosine wave.
- Change the blink/fade period on the fly.
- Enable and disable the LED without losing the current state.
- Set custom brightness limits for fading.
- Non-blocking operation.

## Installation

1.  Download the latest release from the [releases page](https://github.com/marcio-pessoa/Blinker/releases).
2.  In the Arduino IDE, go to `Sketch` > `Include Library` > `Add .ZIP Library...` and select the downloaded file.
3.  You can now use the library by including it in your sketch: `#include <Blinker.h>`

Alternatively, you can install it using the Arduino Library Manager:

1.  In the Arduino IDE, go to `Sketch` > `Include Library` > `Manage Libraries...`
2.  Search for "Blinker" and install the one by Márcio Pessoa.

## Usage

Here's a simple example of how to blink an LED on pin 13 every second:

```cpp
#include <Blinker.h>

Blinker led(13, 1000);

void setup() {
  led.begin();
}

void loop() {
  led.blink();
}
```

### Fading an LED

To fade an LED, use the `fade()` method.

```cpp
#include <Blinker.h>

Blinker led(9, 2000); // Fade over 2 seconds on pin 9

void setup() {
  led.begin();
}

void loop() {
  led.fade();
}
```

### Changing the Period

You can change the blink or fade period at any time with `periodWrite()`:

```cpp
#include <Blinker.h>

Blinker led(13, 1000);

void setup() {
  led.begin();
}

void loop() {
  led.blink();
  // After 5 seconds, change the period to 200ms
  if (millis() > 5000) {
    led.periodWrite(200);
  }
}
```

### API

- `Blinker(byte pin, unsigned int millis_period = 1000, bool state = false)`: Constructor.
- `void begin()`: Initializes the pin. Call this in `setup()`.
- `bool blink()`: Blinks the LED. Call this in `loop()`. Returns `true` if the state changed.
- `bool fade()`: Fades the LED. Call this in `loop()`. Returns `true` if the cycle completes.
- `void periodWrite(unsigned int millis_period)`: Sets a new period.
- `unsigned int periodRead()`: Returns the current period.
- `void enable()`: Enables the blinker.
- `void disable()`: Disables the blinker and turns the LED off.
- `bool status()`: Returns `true` if the blinker is enabled.
- `void off()`: Turns the LED off immediately.
- `bool fadeLimits(int min, int max)`: Sets the min and max brightness for fading (0-255). Returns `true` on error.

## License

This library is released under the MIT License.
