#pragma once

// 1 - LMB / 2 - MMB / 3 - RMB

#include "../types/vectors.hpp"
#include <SDL2/SDL_events.h>

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
	unsigned int clicks = 0; // Clicks made

	Vector2f direction;
	Vector2i axis;

	void handle_event(const SDL_Event& event);
	void set_position(const unsigned int x, const unsigned int y);
	// void set_position(const Window& window, const unsigned int x, const unsigned int y);
};
