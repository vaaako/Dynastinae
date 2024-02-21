#include "../include/window/window.hpp"
#include "../include/shapes/2d/renderer2d.hpp"
#include "../include/shapes/3d/renderer3d.hpp"


// #include "../include/shapes/3d/pyramid.hpp"

#include <iostream>

// See: https://wiki.libsdl.org/SDL2/SDLKeycodeLookup 
void process_keyboard(Window& window, Keyboard keyboard) {
	if(keyboard.down == 27) { // 27 - ESC
		std::cout << "Closing" << std::endl;
		window.close();
	}
}

/**
 * TODO --
 * - Texture "PNG" support
 * - Custom vertex colors for 2D?
 *   + 
 * - How 3d will work for different and custom shapes?
 *   - Be able to add to VBO at any time?
 * */

int main() {
	Window window = Window("Hello Knuppel", 800, 600, true, true);

	Texture texture = Texture("src/texture.jpg");
	Renderer2D renderer = Renderer2D();
	Renderer3D renderer3d = Renderer3D(45.0f, 0.1f, 100.0f); // Set camera


	// Pyramid pyramid(100.0f, 100.0f, 10.0f, 10.0f, Color { 1.0f, 1.0f, 1.0f }, 45.0f);
	// pyramid.bind_texture(texture);

	float rotation = 0.0f;


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

		renderer.set_color(Color { 1.0f, 1.0f, 0.0f });
		renderer.triangle(texture, 100.0f, 100.0f, 100.0f, 50.0f, false, Color(0.0f, 1.0f, 0.0f));
		renderer.triangle(300.0f, 250.0f, 100.0f);

		// renderer.set_color(Color { 0.0f, 1.0f, 1.0f });
		renderer.rectangle(texture, 200.0f, 150.0f, 200.0f, 200.0f, rotation);
		// renderer.rectangle(250.0f, 100.0f, 200.0f, 200.0f);
		renderer.rectangle(350.0f, 300.0f, 200.0f, 200.0f, Color(0.0f, 0.0f, 1.0f));

		rotation += 1.0f;

		renderer3d.pyramid(texture, 10.0f, 100.0f, 100.0f, 100.0f, Color(0.0, 1.0f, 1.0f), rotation);
		// renderer3d.pyramid(100.0f, 100.0f, 100.0f, 100.0f, Color(0.0f, 1.0f, 1.0f), rotation);


		window.swap();

		// Each one second
		window.set_title("Hello Knuppel | FPS: " + std::to_string(window.fps()));
		// std::cout << "FPS: " + std::to_string(window.fps()) << std::endl;

	}
}
