#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>

namespace morse {

using SignalCallback = std::function<void()>;
using WaitCallback = std::function<void(uint32_t)>;

// Encodes plain text to Morse notation.
// Letters are separated by one space, words by three spaces.
std::string encode(std::string_view text);

// Sends text as Morse by invoking start()/stop() and sleeping between signals.
// Uses Raspberry Pi Pico sleep_ms internally.
void transmit(std::string_view text,
              const SignalCallback &start,
              const SignalCallback &stop,
              uint32_t unit_ms = 100);

// Same as above, but timing is delegated to a callback for better testability
// and platform independence.
void transmit(std::string_view text,
              const SignalCallback &start,
              const SignalCallback &stop,
              uint32_t unit_ms,
              const WaitCallback &wait);

} // namespace morse
