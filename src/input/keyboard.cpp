#include "Dynastinae/input/keyboard.hpp"


void Keyboard::handle_event(const SDL_Event& event) {
	uint32 scancode = event.key.keysym.scancode;

	// If key is in state of pressed, don't change until is released
	if(event.key.state != 0 && this->keystate[scancode] == Keystate::PRESSED) {
		return;
	}

	this->keystate[scancode] = static_cast<Keystate>(event.key.state);
}

bool Keyboard::ispressed(const Keycode& key) {
	uint32 scancode = static_cast<uint32>(key);

	// If is down, change state to "pressed"
	if(this->keystate.at(scancode) == Keystate::DOWN) {
		this->keystate[scancode] = Keystate::PRESSED;
		return true;
	}

	return false;
}
