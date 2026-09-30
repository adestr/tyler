#include <stdio.h>
#include "pico/stdlib.h"
#include "tyler.hpp"

namespace board = servo::servo2040;

const uint SPEED = 5;

constexpr float BRIGHTNESS = 0.4f;

const uint UPDATES = 50;

plasma::WS2812 led_bar(board::NUM_LEDS, pio1, 0, board::LED_DATA);

Button user_sw(board::USER_SW);

/**
 * Turns all LEDs on with a green color.
 */
void on() {
    for (auto i = 0u; i < board::NUM_LEDS; ++i) {
        led_bar.set_hsv(i, 0.333f, 1.0f, BRIGHTNESS);
    }
}

/**
 * Turns all LEDs off.
 */
void off() {
    led_bar.clear();
}

int main() {
    stdio_init_all();

    led_bar.start();

    morse::transmit("EVENLODE TECHNOLOGY", on, off, 5);

    float offset = 0.0f;
    float increment = (float)SPEED / 1000.0f;

    while (!user_sw.raw()) {
        offset += increment;

        for (auto i = 0u; i < board::NUM_LEDS; ++i) {
            float hue = fmodf(offset + (float)i / (float)board::NUM_LEDS, 1.0f);
            led_bar.set_hsv(i, hue, 1.0f, BRIGHTNESS);
        }

        sleep_ms(1000 / UPDATES);
    }

    led_bar.clear();

    sleep_ms(100);
}
