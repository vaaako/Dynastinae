#include "../include/window/window.hpp"
#include "../include/shapes/renderer/renderer2d.hpp"
#include "../include/shapes/renderer/renderer3d.hpp"
#include "../include/types/audio.hpp"
#include "../include/types/font.hpp"

#include <iostream>

// MUSIC - Play only one at the channel
// SOUND - Can play multple at the same channel
Audio* mp3 = new Audio("src/sound.mp3", false);
Audio* wav = new Audio("src/sound2.wav", true);

// See: https://wiki.libsdl.org/SDL2/SDLKeycodeLookup 
void process_keyboard(Window& window, Keyboard keyboard) {
	// 27 - ESC
	if(keyboard.down == 27 || keyboard.down == SDLK_ESCAPE) {
		std::cout << "Closing" << std::endl;
		window.close();
	}

	if(keyboard.down == SDLK_RETURN) {}

	if(keyboard.down == SDLK_z) {
		mp3->set_volume(50);
		mp3->play(0);
	}

	if(keyboard.down == SDLK_x) {
		wav->set_volume(50);
		wav->play();
	}

}


/**
 * TODO --
 * - Custom vertex colors for 2D?
 *   + Later
 *   + Add to vertex attrib 2 on shape VBO and check if is to use on shape instance
 *  
 * - .obj
 *   + When creating a OBJ `OBJ obj = Obj()` -> `obj.draw()`. This makes a new VAO and VBO of that obj
 *  
 * - Line
 * - Skybox
 *  
 * - Use Vector2f and Vector3f instead of glm versions
 * - Unify shader and shader_texture somehow
 * - Code keyboard enums
 * - More window events
 * */

int main() {
	Window window = Window("Hello Knuppel", 800, 600, true, true);

	Texture* texture = new Texture("src/texture.jpg", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture* kuromi = new Texture("src/kuromi.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture* brick = new Texture("src/brick.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);

	Font* font = new Font("src/msgothic.ttf", "Hello World!");


	Renderer2D renderer = Renderer2D();
	Renderer3D renderer3d = Renderer3D(45.0f, 0.1f, 100.0f); // Set camera

	float rotation = 0.0f;
	while(window.is_open()) {
		window.clear({ 255, 127, 255 });
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


		renderer.triangle(brick, 100.0f, 100.0f, 100.0f, 50.0f, Color(0, 255, 0));
		renderer.rectangle(brick, 50.0f, 100.0f, 200.0f, 200.0f);

		renderer.triangle(550.0f, 350.0f, 100.0f, rotation);
		renderer.rectangle(500.0f, 370.0f, 200.0f, 200.0f, Color(0, 0, 255));


		// Don't worry about draw order with 2D, 2D shapes are always above 3D shapes
		renderer3d.pyramid(texture, -1.0f, -1.0f, -7.0f, rotation, { 0, 255, 0 });
		renderer3d.cube(kuromi, 1.0f, 1.0f, -8.0f, rotation, { 255, 255, 0 });


		renderer.draw_font(*font, 10.0f, 10.0f);

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
