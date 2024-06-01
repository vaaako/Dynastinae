#pragma once

#include <SDL2/SDL_events.h>
#include "Dynastinae/types.hpp"
#include "Dynastinae/types/vector/vec2.hpp"

enum class MouseBTN {
	LMB = 1,
	MMB = 2,
	RMB = 3,
	NONE = 4
};

enum class Scroll {
	NONE = 0,
	UP = 1,
	DOWN = -1
};

// TODO -- Make a inputs vector like in keyboard.hpp? idk if it's necessary
struct Mouse {
	uint32 clicks = 0; // Clicks made
	Scroll scroll = Scroll::NONE; // 

	vec2<int> position; // Mouse click position
	vec2<int> motion; // Mouse motion position
	vec2<int> direction;

	void handle_event(const SDL_Event& event);
	void set_position(const int x, const int y);
	// void set_position(const Window& window, const uint32 x, const uint32 y);

	inline bool isclick(const MouseBTN btn) const {
		return this->down == btn;
	}

	inline bool isup(const MouseBTN btn) const {
		return this->up == btn;
	}

	private:
		MouseBTN up = MouseBTN::NONE; // Last button up
		MouseBTN down = MouseBTN::NONE;
};
