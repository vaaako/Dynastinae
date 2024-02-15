#include "../include/window/window.hpp"
#include "../include/shapes/triangle.hpp"
#include "../include/shapes/rectangle.hpp"

#include <iostream>

// See: https://wiki.libsdl.org/SDL2/SDLKeycodeLookup 
void process_keyboard(Window& window, Keyboard keyboard) {
	if(keyboard.down == 27) {
		std::cout << "Closing" << std::endl;
		window.close();
	}
}

/**
 * TODO --
 * - Texture "PNG" support
 *
 * */


int main() {
	Window window = Window("Hello Knuppel", 800, 600, true);

	Texture texture = Texture("src/texture.jpg");

	// Triangle triangle(500.0f, 400.0f, 100.0f, Color { 1.0f, 1.0f, 0.0f });
	Triangle triangle(450.0f, 300.0f, 300.0f);
	triangle.bind_texture(texture);

	Rectangle rectangle(250.0f, 350.0f, 100.0f, 100.0f);
	rectangle.bind_texture(texture);

	Rectangle rainbow(100.0f, 100.0f, 300.0f, 300.0f,
		{
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f
		}
	);
	rainbow.bind_texture(texture);


	// Texture tex_background = Texture("src/background.jpg");
	// Rectangle background = Rectangle(0.0f, 0.0f, (float)window.get_width(), (float)window.get_height());
	// background.bind_texture(tex_background);


	while(window.is_open()) {
		window.clear(1.0f, 0.5f, 1.0f);
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

		// background.draw();
		triangle.draw(true);
		rainbow.draw();
		rectangle.draw();

		window.swap();
	}
}
