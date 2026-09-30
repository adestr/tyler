#include "morse.hpp"

#include <cctype>
#include <unordered_map>

#include "pico/stdlib.h"

namespace {

const std::unordered_map<char, std::string_view> kMorseMap = {
	{'A', ".-"},   {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},  {'E', "."},
	{'F', "..-."}, {'G', "--."},  {'H', "...."}, {'I', ".."},   {'J', ".---"},
	{'K', "-.-"},  {'L', ".-.."}, {'M', "--"},   {'N', "-."},   {'O', "---"},
	{'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},  {'S', "..."},  {'T', "-"},
	{'U', "..-"},  {'V', "...-"}, {'W', ".--"},  {'X', "-..-"}, {'Y', "-.--"},
	{'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
	{'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."},
	{'9', "----."},
	{'.', ".-.-.-"}, {',', "--..--"}, {'?', "..--.."}, {'!', "-.-.--"},
	{'/', "-..-."},  {'-', "-....-"}, {'(', "-.--."},  {')', "-.--.-"},
	{'@', ".--.-."}, {':', "---..."}, {';', "-.-.-."}, {'=', "-...-"},
	{'+', ".-.-."},  {'_', "..--.-"}, {'\'', ".----."}, {'"', ".-..-."},
	{'$', "...-..-"}};

} // namespace

namespace morse {

std::string encode(std::string_view text) {
	std::string output;
	bool first_token = true;
	bool pending_word_gap = false;

	for (char ch : text) {
		if (std::isspace(static_cast<unsigned char>(ch))) {
			pending_word_gap = true;
			continue;
		}

		const char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
		const auto it = kMorseMap.find(upper);
		if (it == kMorseMap.end()) {
			continue;
		}

		if (!first_token) {
			output += pending_word_gap ? "   " : " ";
		}

		output += it->second;
		first_token = false;
		pending_word_gap = false;
	}

	return output;
}

void transmit(std::string_view text,
			  const SignalCallback &start,
			  const SignalCallback &stop,
			  uint32_t unit_ms,
			  const WaitCallback &wait) {
	const std::string morse_text = encode(text);

	for (size_t i = 0; i < morse_text.size();) {
		const char token = morse_text[i];

		if (token == '.' || token == '-') {
			start();
			wait(token == '.' ? unit_ms : 3 * unit_ms);
			stop();

			if (i + 1 < morse_text.size()) {
				if (morse_text[i + 1] == '.' || morse_text[i + 1] == '-') {
					wait(unit_ms);
				}
			}

			++i;
			continue;
		}

		size_t space_count = 0;
		while (i < morse_text.size() && morse_text[i] == ' ') {
			++space_count;
			++i;
		}

		if (space_count >= 3) {
			wait(7 * unit_ms);
		} else if (space_count >= 1) {
			wait(3 * unit_ms);
		}
	}
}

void transmit(std::string_view text,
			  const SignalCallback &start,
			  const SignalCallback &stop,
			  uint32_t unit_ms) {
	transmit(text, start, stop, unit_ms, [](uint32_t delay_ms) {
		sleep_ms(delay_ms);
	});
}

} // namespace morse
