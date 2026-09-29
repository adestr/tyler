#include <stdio.h>
#include "pico/stdlib.h"
#include "tyler.hpp"

using namespace plasma;
using namespace servo;

const uint SPEED = 5;

constexpr float BRIGHTNESS = 0.4f;

const uint UPDATES = 50;

WS2812 led_bar(servo2040::NUM_LEDS, pio1, 0, servo2040::LED_DATA);

Button user_sw(servo2040::USER_SW);

int main() {
    stdio_init_all();

    led_bar.start();

    float offset = 0.0f;
    float increment = (float)SPEED / 1000.0f;

    while (!user_sw.raw()) {
        offset += increment;

        for (auto i = 0u; i < servo2040::NUM_LEDS; ++i) {
            float hue = fmodf(offset + (float)i / (float)servo2040::NUM_LEDS, 1.0f);
            led_bar.set_hsv(i, hue, 1.0f, BRIGHTNESS);
        }

        sleep_ms(1000 / UPDATES);
    }

    led_bar.clear();

    sleep_ms(100);
}
