#include <Dynastinae/types/font.hpp>
#include <Dynastinae/window/window.hpp>


void process_keyboard(Window& window, Keyboard& keyboard) {
	// Close if press ESC
	if(keyboard.isdown(Keycode::ESCAPE)) {
		window.close();
	}
}

int main() {
	Window window = Window("Hello Dynastinae! | FPS: 0", 800, 600);

	// Timer
	uint32 start_time = window.time(); // Runs since init
	while(window.is_open()) {
		// Clear screen with color
		window.clear({ 255, 127, 255 });

		// Process all frame events
		window.process_events();
		process_keyboard(window, *window.keyboard());

		// If click to close window
		if(window.trigger_event(Event::QUIT)) {
			window.close();
		}

		// Update FPS each second
		uint32 current_time = window.time();

		// Check if elapsed 1 second
		if(current_time - start_time >= 1000) {
			window.set_title("Hello Dynastinae! | FPS: " + std::to_string(window.fps()));
			start_time = window.time();
		}

		// Swap buffers
		window.swap_buffers();
	}
}
