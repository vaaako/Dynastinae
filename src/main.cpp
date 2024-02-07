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


    std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr_w(10, window.get_width());
	std::uniform_int_distribution<> distr_h(10, window.get_height());
	std::uniform_int_distribution<> distr_size(10, 50);

	std::vector<Rectangle> rects;
	std::vector<Triangle> triangs;
	for(int i = 0; i < 100; i++) {
		const float x = (float)(distr_w(gen));
		const float y = (float)(distr_h(gen));

		const float r = (static_cast<float>(std::rand()) / RAND_MAX);
		const float g = (static_cast<float>(std::rand()) / RAND_MAX);
		const float b = (static_cast<float>(std::rand()) / RAND_MAX);
		rects.push_back( Rectangle(x, y, (float)distr_size(gen), (float)(distr_size(gen)), { r, g, b }) );
	}

	for(int i = 0; i < 100; i++) {
		const float x = (float)(distr_w(gen));
		const float y = (float)(distr_h(gen));

		const float r = (static_cast<float>(std::rand()) / RAND_MAX);
		const float g = (static_cast<float>(std::rand()) / RAND_MAX);
		const float b = (static_cast<float>(std::rand()) / RAND_MAX);
		triangs.push_back( Triangle(x, y, (float)distr_size(gen), { r, g, b }) );
	}



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

		// triangle.draw();
		// rectangle.draw();
		// rectangle2.draw();

		for(long unsigned int i = 0; i < rects.size(); i++) {
			rects.at(i).draw();
			triangs.at(i).draw();
		}

		window.swap();
	}
}
