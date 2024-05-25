#include "../../include/input/mouse.hpp"

// #include <iostream>

void Mouse::handle_event(const SDL_Event& event) {
	if(event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_MouseButtonEvent button = event.button;

		// Click location
		this->axis.set_values(button.x, button.y);

		// std::cout << "Mouse Pressed button: " << (int)button.button << std::endl;
		this->down = static_cast<MouseBTN>(button.button); // Button clicked
		this->up = MouseBTN::NONE; // No buttons pressed
		this->clicks = button.clicks;

	} else if(event.type == SDL_MOUSEBUTTONUP) {
		this->up = static_cast<MouseBTN>(event.button.button);
		this->down = MouseBTN::NONE;

		this->clicks = 0;
		this->axis.clear();
	}

	if(event.type == SDL_MOUSEMOTION) {
		SDL_MouseMotionEvent motion = event.motion;
		// std::cout << "Mouse Motion: " << event.motion.x << ":" << event.motion.y << std::endl;
		// std::cout << "Mouse dir: " << event.motion.xrel << ":" << event.motion.yrel << std::endl;

		this->axis.set_values(motion.x, motion.y);
		this->direction.set_values(event.motion.xrel, event.motion.yrel);
	}
}

void Mouse::set_position(const uint32 x, const uint32 y) {
	this->axis.set_values(x, y);
}

// void Mouse::set_position(const Window& window, const uint32 x, const uint32 y) {
// 	SDL_WarpMouseInWindow(window, x, y);
// 	this->x = x;
// 	this->y = y;
// }
