#include <stdio.h>
#include "pico/stdlib.h"
#include "tyler.hpp"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

int led_init(void) {
#ifdef PICO_DEFAULT_LED_PIN
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, true);
    return 0;
#else
    return -1;
#endif
}

int main() {
    stdio_init_all();
    printf("Hello, world!\n");
    if (led_init() == 0) {
        while (true) {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            sleep_ms(LED_DELAY_MS);
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            sleep_ms(LED_DELAY_MS);
        }
    }
    return 0;
}
