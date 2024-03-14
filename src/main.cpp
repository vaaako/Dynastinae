#include "../include/window/window.hpp"
#include "../include/shapes/renderer/renderer2d.hpp"
#include "../include/shapes/renderer/renderer3d.hpp"

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
 *   + Later
 *   + Add to vertex attrib 2 on shape VBO and check if is to use on shape instance
 * - How 3d will work for different and custom shapes?
 *   + VAO for each VBO
 *   + When creating a OBJ `OBJ obj = Obj()` -> `obj.draw()`. This makes a new VAO and VBO of that obj
 *  
 * - shape.hpp
 * - Pyramid and Cube on Renderer3D
 * - Unify shader and shader_texture somehow
 * */

int main() {
	Window window = Window("Hello Knuppel", 800, 600, true, true);

	// Texture* texture = new Texture("src/texture.jpg", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture* texture = new Texture("src/brick.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Renderer2D renderer = Renderer2D();
	Renderer3D renderer3d = Renderer3D(45.0f, 0.1f, 100.0f); // Set camera

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


		renderer.triangle(texture, 100.0f, 100.0f, 100.0f, 50.0f, false, Color(0.0f, 1.0f, 0.0f));
		renderer.triangle(300.0f, 250.0f, 100.0f);

		renderer.rectangle(texture, 250.0f, 100.0f, 200.0f, 200.0f);
		renderer.rectangle(350.0f, 300.0f, 200.0f, 200.0f, Color(0.0f, 0.0f, 1.0f));


		// Don't worry about draw order with 2D, 2D shapes are always above 3D shapes
		// renderer3d.pyramid(texture, 0.0f, 0.0f, -4.0f, rotation, { 0.0f, 1.0f, 0.0f });

		renderer3d.cube(texture, 0.0f, 0.0f, -4.0f, rotation, { 0.0f, 1.0f, 0.0f });

		rotation += 1.0f;

		if(rotation > 360.0f) {
			rotation = 0.0f;
		}

		// Each one second
		window.set_title("Hello Knuppel | FPS: " + std::to_string(window.fps()));

		window.swap();

	}

	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		std::cout << "~> OpenGL error code: " << err << std::endl;
	}
}
