#pragma once

// 1 - LMB / 2 - MMB / 3 - RMB

struct Mouse {
	unsigned int down = -1;
	unsigned int up = -1; // Last button up
	unsigned int clicks = 0;

	unsigned int x = - 1;
	unsigned int y = -1;

	unsigned int dir_x = -1;
	unsigned int dir_y = -1;


	inline void btndown(const int x, const int y, const unsigned int button, const unsigned int clicks) {
		// this->down = true;
		this->x = x;
		this->y = y;

		this->down = button;
		this->up = -1;
		this->clicks = clicks;
	}

	inline void btnup(const unsigned int button) {
		// this->down = false;
		this->up = button;
		this->down = -1;

		this->clicks = 0;
		this->x = -1;
		this->y = -1;
	}

	inline void motion(const unsigned int x, const unsigned int y, const unsigned int dir_x, const unsigned int dir_y) {
		this->x = x;
		this->y = y;
		this->dir_x = dir_x;
		this->dir_y = dir_y;
	}

};