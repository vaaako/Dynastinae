#include "../include/window/window.hpp"
#include "../include/shapes/renderer/renderer2d.hpp"
#include "../include/shapes/renderer/camera.hpp"
#include "../include/types/audio.hpp"
#include "../include/types/font.hpp"

#include <iostream>


// https://wiki.libsdl.org/SDL2/SDL_Scancode
// Handle keyboard
void process_keyboard(Window& window, Keyboard& keyboard) {
	if(keyboard.isdown(Keycode::ESCAPE)) {
		window.close();
	}
}

// Move camera
void move_camera(Keyboard& keyboard, Camera& camera) {
	if(keyboard.isdown(Keycode::W)) {
		camera.go_foward();
	} else if(keyboard.isdown(Keycode::S)) {
		camera.go_back();
	}

	if(keyboard.isdown(Keycode::A)) {
		camera.go_left();
	} else if(keyboard.isdown(Keycode::D)) {
		camera.go_right();
	}

	if(keyboard.isdown(Keycode::LSHIFT)) {
		camera.go_up();
	} else if(keyboard.isdown(Keycode::LCTRL)) {
		camera.go_down();
	}
}




/** INFO CURRENTLY WORKING ON
 * - Make own events enums like i did with keyboard
 * */

int main() {
	Window window = Window("Hello Dynastinae", 800, 600, true, true);

	Texture texture = Texture("src/texture.jpg", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture kuromi = Texture("src/kuromi.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture brick = Texture("src/brick.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);

	// MUSIC - Play only one at the channel
	// SOUND - Can play multple at the same channel
	Audio mp3 = Audio("src/sound.mp3", false); // Path, is music
	Audio wav = Audio("src/sound2.wav", true);

	Font font = Font("src/msgothic.ttf", "FPS: 0", 24, { 255 }); // Path, Text, Size, Color

	// Renders
	Renderer2D renderer = Renderer2D(window);
	Camera camera = Camera(window); // 3D environment


	float rotation = 0.0f;
	uint32 start_time = window.time();
	while(window.is_open()) {
		// Clear screen with color
		window.clear({ 255, 127, 255 });

		// Process all frame events
		window.process_events();

		// If click to close window
		if(window.trigger_event(SDL_QUIT)) {
			window.close();
		}

		// Handle some events
		process_keyboard(window, *window.keyboard());
		move_camera(*window.keyboard(), camera);
		camera.rotate(window, *window.mouse());


		// Draw 2D Shapes
		// renderer.triangle(brick, { 100.0f, 100.0f }, 100.0f, 50.0f, Color(0, 255, 0));
		// renderer.rectangle(brick, { 50.0f, 100.0f }, 200.0f, 200.0f);
		//
		// renderer.triangle({ 550.0f, 350.0f }, 100.0f, rotation);
		// renderer.rectangle({ 500.0f, 370.0f }, 200.0f, 200.0f, Color::from_hex(0xCA1773));


		// Don't worry about draw order with 2D, 2D shapes are always above 3D shapes
		camera.pyramid(&texture, { -1.0f, -1.0f, -7.0f }, rotation, { 0, 1.0f, 0 });
		// camera.cube(&kuromi, { 1.0f, 1.0f, -8.0f }, rotation, { 1.0f, 1.0f, 1.0f });


		// Update FPS each seconds
		uint32 current_time = window.time();
		if(current_time - start_time >= 1000) {
			font.set_text("FPS: " + std::to_string(window.fps()));
			start_time = window.time();
		}

		// Draw fps
		renderer.draw_font(font, { 10.0f, 10.0f });

		// Rotate
		rotation += 1.0f;
		if(rotation > 360.0f) {
			rotation = 0.0f;
		}

		// Swap buffers and all updates needed on frame end
		window.swap();
	}

	// Check for any OpenGL error
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		std::cout << "~> OpenGL error code: " << err << std::endl;
	}
}
