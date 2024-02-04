#pragma once

struct Keyboard {
	unsigned int down = -1;
	unsigned int up = -1; // Last button up
	unsigned int holding = -1;
	unsigned int repeat = 0;
	// bool down = false;


	inline void keydown(const unsigned int key, const bool repeat) {
		this->down = key;
		this->up = -1;
		if(repeat) {
			this->holding = key;
			return;
		}

	}

	inline void keyup(const unsigned int key) {
		// this->down = false;
		this->down = -1;
		this->up = key;
		this->repeat = -1;
	}
};