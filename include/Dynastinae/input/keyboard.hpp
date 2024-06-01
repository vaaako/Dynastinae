#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include "Dynastinae/types.hpp"
#include "keycode.hpp"

enum class Keystate {
	UP,
	DOWN,
	PRESSED
};

struct Keyboard {
	// Handle events from window
	void handle_event(const SDL_Event& event);
	bool ispressed(const Keycode& key);

	inline bool isdown(const Keycode& key) const {
		return (this->keystate.at(static_cast<uint32>(key)) == Keystate::DOWN);
	}

	inline bool isup(const Keycode& key) const {
		return (this->keystate.at(static_cast<uint32>(key)) == Keystate::UP);
	}



	inline void set_keystate(const Keycode& key, const Keystate& state) {
		this->keystate[static_cast<uint32>(key)] = state;
	}

	inline Keystate get_keystate(const Keycode& key) const {
		return this->keystate[static_cast<uint32>(key)];
	}

	private:
		// Init vector with the size of SDL scancodes with the value 0 (RELEASED)
		std::vector<Keystate> keystate = std::vector<Keystate>(SDL_NUM_SCANCODES, Keystate::UP);
};
