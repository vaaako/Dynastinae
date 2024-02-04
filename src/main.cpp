#include <SDL2/SDL_events.h>
#include <iostream>

#include "../include/window/window.hpp"
#include "../include/opengl/vao.hpp"
#include "../include/opengl/vbo.hpp"
#include "../include/opengl/ebo.hpp"
#include "../include/opengl/shader_program.hpp"
#include "../include/shapes/triangle.hpp"
#include "../include/shapes/square.hpp"


// TODO -- Make base "shape" class and triangle and square child of it

void process_keyboard(Window& window, Keyboard keyboard) {
	if(keyboard.down == 27) {
		std::cout << "Closing" << std::endl;
		window.close();
	}
}

int main() {
	Window window = Window("Hello Knuppel", 800, 600, true);

	Triangle triangle(0.0f, 0.0f, 0.5f, 0.5f);  // Triangle at (0, 0) with width 0.5 and height 0.5
	Square square(0.0f, 0.0f, 0.5f, 0.5f);

	while(window.is_open()) {
		window.clear(0.2f, 0.3f, 0.3f, 1.0f);

		switch (window.process_event()) {
			case Event::QUIT:
				window.close();
				break;

			case Event::KEYDOWN:
			case Event::KEYUP:
				process_keyboard(window, window.keyboard());
				break;

			default:
				break;
		}

		square.draw();
		triangle.draw();

		window.swap();
	}
}
