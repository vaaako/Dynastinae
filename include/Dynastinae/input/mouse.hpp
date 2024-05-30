#pragma once

// 1 - LMB / 2 - MMB / 3 - RMB

#include <SDL2/SDL_events.h>
#include "Dynastinae/types/default.hpp"
#include "Dynastinae/types/vector/vec2.hpp"

enum class MouseBTN {
	LMB = 1,
	MMB = 2,
	RMB = 3,
	NONE = 4
};

// TODO -- Make a inputs vector like in keyboard.hpp? idk if it's necessary
struct Mouse {
	MouseBTN up = MouseBTN::NONE; // Last button up
	MouseBTN down = MouseBTN::NONE;
	uint32 clicks = 0; // Clicks made

	vec2<int> direction;
	vec2<int> axis;

	void handle_event(const SDL_Event& event);
	void set_position(const int x, const int y);
	// void set_position(const Window& window, const uint32 x, const uint32 y);
};
