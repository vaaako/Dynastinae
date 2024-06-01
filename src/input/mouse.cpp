#include "Dynastinae/input/mouse.hpp"
#include <SDL2/SDL_events.h>

#include <iostream>

void Mouse::handle_event(const SDL_Event& event) {
	// CLICK //
	if(event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_MouseButtonEvent button = event.button;

		// Click location
		this->position.set_values(button.x, button.y);

		
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

		this->motion.set_values(motion.x, motion.y);
		this->direction.set_values(event.motion.xrel, event.motion.yrel);

	}


	// SCROLL //
	if(event.type == SDL_MOUSEWHEEL) {
		// std::cout << "Wheel: " << event.wheel.preciseY << std::endl;
		this->scroll = static_cast<Scroll>(event.wheel.y);
	}
}

void Mouse::set_position(const int x, const int y) {
	this->position.set_values(x, y);
}

// void Mouse::set_position(const Window& window, const uint32 x, const uint32 y) {
// 	SDL_WarpMouseInWindow(window, x, y);
// 	this->x = x;
// 	this->y = y;
// }
