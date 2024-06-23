#include "Dynastinae/input/mouse.hpp"
#include "Dynastinae/utils/log.hpp"
#include "Dynastinae/window/window.hpp"

// #include <iostream>

void Mouse::handle_event(const SDL_Event& event) {
	// CLICK //
	if(event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_MouseButtonEvent button = event.button;

		// Click location
		this->position.set_values(static_cast<uint32>(button.x), static_cast<uint32>(button.y));

		this->up = MouseBTN::NONE; // No buttons pressed
		this->down = static_cast<MouseBTN>(button.button); // Button clicked
		this->clicks = button.clicks;
	} else if(event.type == SDL_MOUSEBUTTONUP) {
		this->up = static_cast<MouseBTN>(event.button.button);
		this->down = MouseBTN::NONE;

		this->clicks = 0;
		this->position.clear();
	}


	// MOTION //
	if(event.type == SDL_MOUSEMOTION) {
		SDL_MouseMotionEvent motion = event.motion;
		// std::cout << "Mouse Motion: " << event.motion.x << ":" << event.motion.y << std::endl;
		// std::cout << "Mouse dir: " << event.motion.xrel << ":" << event.motion.yrel << std::endl;

		this->motion.set_values(static_cast<uint32>(motion.x), static_cast<uint32>(motion.y));
		this->direction.set_values(event.motion.xrel, event.motion.yrel);

	}


	// SCROLL //
	if(event.type == SDL_MOUSEWHEEL) {
		// std::cout << "Wheel: " << event.wheel.preciseY << std::endl;
		this->scroll = static_cast<Scroll>(event.wheel.y);
	}
}

void Mouse::set_cursor_position(const Window& window, const uint32 x, const uint32 y) {
	int int_x = static_cast<int>(x);
	int int_y = static_cast<int>(y);
	
	if(window.out_of_bounds(int_x, int_y)) {
		LOG_ERROR("x or y args are out of window bounds");
		return;
	}

	SDL_WarpMouseInWindow(window.get_reference(), int_x, int_y);
	this->position.set_values(x, y);
}
