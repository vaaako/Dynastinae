#include <SDL2/SDL_events.h>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "../include/window/window.hpp"
#include "../include/opengl/shader_program.hpp"
#include "../include/shapes/triangle.hpp"
#include "../include/shapes/rectangle.hpp"

#include <random>


void process_keyboard(Window& window, Keyboard keyboard) {
	if(keyboard.down == 27) {
		std::cout << "Closing" << std::endl;
		window.close();
	}
}

int main() {
	Window window = Window("Hello Knuppel", 800, 600, true);

	// Triangle triangle(500.0f, 400.0f, 50.0f);  // Triangle at (0, 0) with width 0.5 and height 0.5
	// Rectangle rectangle(100.0f, 200.0f, 50, 50, { 1, 0, 0 });
	// Rectangle rectangle2(300.0f, 250.0f, 70, 70);


	// Triangle triangle(100, 100, 50.0f);
	// Triangle triangle(100, 100, 50.0f, Color { 1.0f, 1.0f, 0.0f });
	// Triangle triangle(100, 100, 50.0f,
	// 	{
	// 		1.0f, 0.0f, 0.0f,
	// 		0.0f, 1.0f, 0.0f,
	// 		0.0f, 0.0f, 1.0f
	// 	}
	// );


	// Rectangle triangle(100, 100, 50.0f, 50.0f);
	Rectangle triangle(100, 100, 50.0f, 50.0f, Color { 1.0f, 1.0f, 0.0f });
	// Rectangle triangle(100, 100, 50.0f, 50.0f
	// 	{
	// 		1.0f, 0.0f, 0.0f,
	// 		0.0f, 1.0f, 0.0f,
	// 		0.0f, 0.0f, 1.0f
	// 	}
	// );

	while(window.is_open()) {
		window.clear(1.0, 0.5, 1.0);
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

		triangle.draw();
		// rectangle.draw();
		// rectangle2.draw();

		window.swap();
	}
}
