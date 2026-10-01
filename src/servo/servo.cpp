#include "pico/stdlib.h"

#include "servo2040.hpp"

namespace board = servo::servo2040;

const uint WAIT_INTERVAL_MS = 2000;

const uint SWEEPS = 1;

const uint STEPS = 5;

const uint STEPS_INTERVAL_MS = 1000;

constexpr float SWEEP_EXTENT = 90.0f;

servo::Servo s1 = servo::Servo(board::SERVO_1);

namespace servo_control
{
    void start()
    {
        s1.init();
        s1.enable();

        sleep_ms(WAIT_INTERVAL_MS);

        s1.to_min();
        sleep_ms(WAIT_INTERVAL_MS);

        s1.to_max();
        sleep_ms(WAIT_INTERVAL_MS);

        s1.to_mid();
        sleep_ms(WAIT_INTERVAL_MS);

        // Do a sine sweep
        for (auto j = 0u; j < SWEEPS; j++)
        {
            for (auto i = 0u; i < 360; i++)
            {
                s1.value(sin(((float)i * (float)M_PI) / 180.0f) * SWEEP_EXTENT);
                sleep_ms(20);
            }
        }

        // Do a stepped sweep
        for (auto j = 0u; j < SWEEPS; j++)
        {
            for (auto i = 0u; i < STEPS; i++)
            {
                s1.to_percent(i, 0, STEPS, 0.0 - SWEEP_EXTENT, SWEEP_EXTENT);
                sleep_ms(STEPS_INTERVAL_MS);
            }
            for (auto i = 0u; i < STEPS; i++)
            {
                s1.to_percent(i, STEPS, 0, 0.0 - SWEEP_EXTENT, SWEEP_EXTENT);
                sleep_ms(STEPS_INTERVAL_MS);
            }
        }

        // Disable the servo
        s1.disable();
    }
}