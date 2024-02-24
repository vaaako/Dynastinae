#include "../include/window/window.hpp"
#include "../include/shapes/2d/renderer2d.hpp"
#include "../include/shapes/3d/renderer3d.hpp"

#include <iostream>

// See: https://wiki.libsdl.org/SDL2/SDLKeycodeLookup 
void process_keyboard(Window& window, Keyboard keyboard) {
	// 27 - ESC
	if(keyboard.down == 27) {
		std::cout << "Closing" << std::endl;
		window.close();
	}
}


/**
 * TODO --
 * - Custom vertex colors for 2D?
 *   + 
 * - How 3d will work for different and custom shapes?
 *   - Be able to add to VBO at any time?
 * */

int main() {
	Window window = Window("Hello Knuppel", 800, 600, true, true);

	Texture texture = Texture("src/texture.jpg", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Renderer2D renderer = Renderer2D();
	Renderer3D renderer3d = Renderer3D(45.0f, 0.1f, 100.0f); // Set camera

	renderer.use_custom_color({
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f
	});


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


		// renderer.set_color(Color { 1.0f, 1.0f, 0.0f });
		// renderer.triangle(texture, 100.0f, 100.0f, 100.0f, 50.0f, false, Color(0.0f, 1.0f, 0.0f));
		// renderer.triangle(300.0f, 250.0f, 100.0f);
		// renderer.triangle(false, 300.0f, 250.0f, 100.0f);
		//
		// renderer.set_color(Color { 0.0f, 1.0f, 1.0f });
		// renderer.rectangle(texture, 200.0f, 150.0f, 200.0f, 200.0f, 0.0f, true);
		// renderer.rectangle(250.0f, 100.0f, 200.0f, 200.0f);
		// renderer.rectangle(350.0f, 300.0f, 200.0f, 200.0f, Color(0.0f, 0.0f, 1.0f));
		//
		// // Use custom color
		// renderer.rectangle(true, 350.0f, 300.0f, 200.0f, 200.0f);
		//



		// Don't worry about draw order with 2D, 2D shapes are always above 3D shapes
		// renderer3d.pyramid(texture, 10.0f, 100.0f, 100.0f, 100.0f, rotation);
		// renderer3d.pyramid(10.0f, 100.0f, 100.0f, 100.0f, Color(0.0, 1.0f, 1.0f), rotation);

		renderer3d.cube(texture, 10.0f, 100.0f, 100.0f, 100.0f, 100.0f, rotation);
		// renderer3d.cube(10.0f, 100.0f, 100.0f, 100.0f, 100.0f, Color(0.0, 1.0f, 1.0f), rotation);

		rotation += 1.0f;

		// Each one second
		window.set_title("Hello Knuppel | FPS: " + std::to_string(window.fps()));

		window.swap();

	}
}
