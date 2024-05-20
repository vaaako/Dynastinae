#include "../../include/input/keyboard.hpp"


void Keyboard::handle_event(const SDL_Event& event) {
	unsigned int scancode = event.key.keysym.scancode;

	// If key is in state of pressed, don't change until is released
	if(event.key.state != 0 && this->keystate[scancode] == Keystate::PRESSED) {
		return;
	}

	this->keystate[scancode] = static_cast<Keystate>(event.key.state);
}

bool Keyboard::ispressed(const Keycode& key) {
	unsigned int scancode = static_cast<unsigned int>(key);

	// If is down, change state to "pressed"
	if(this->keystate.at(scancode) == Keystate::DOWN) {
		this->keystate[scancode] = Keystate::PRESSED;
		return true;
	}

	return false;
}
