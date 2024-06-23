#include "Dynastinae/input/keycode.hpp"
#include "Dynastinae/shapes/2d/triangle.hpp"
#include "Dynastinae/shapes/3d/cube.hpp"
#include "Dynastinae/shapes/3d/pyramid.hpp"
#include "Dynastinae/window/window.hpp"
#include "Dynastinae/scenes/scene2d.hpp"
#include "Dynastinae/scenes/scene3d.hpp"
#include "Dynastinae/scenes/camera.hpp"
#include "Dynastinae/types/audio.hpp"
#include "Dynastinae/types/font.hpp"

#include <iostream>

// Handle keyboard
void process_keyboard(Window& window, Keyboard& keyboard) {
	if(keyboard.ispressed(Keycode::ESCAPE)) {
		window.close();
	}
}

void process_camera(Window& window, Keyboard& keyboard, Mouse& mouse, Camera& camera, bool& can_move) {
	// ROTATION //
	// Only rotate when click on screen
	if(mouse.isclick(MouseBTN::LMB) && !can_move) {
		can_move = true;
		mouse.set_cursor_position(window, window.get_width() / 2, window.get_height() / 2); // Prevent cursor from exiting the screen
		window.hide_cursor(true);
		return; // Prevent camera from look where the cursor clicked
	}

	// Rotate camera
	if(can_move) {
		camera.rotate(mouse);
		mouse.set_cursor_position(window, window.get_width() / 2, window.get_height() / 2); // Prevent cursor from exiting the screen
	}

	// Press TAB to not rotate anymore
	if(keyboard.ispressed(Keycode::TAB)) {
		can_move = false;
		window.hide_cursor(false);
	}



	// MOVEMENT //
	if(keyboard.isdown(Keycode::W)) {
		camera.move_foward();
	} else if(keyboard.isdown(Keycode::S)) {
		camera.move_backward();
	}

	// if(keyboard.isdown(Keycode::W)) {
	// 	camera.move_front();
	// } else if(keyboard.isdown(Keycode::S)) {
	// 	camera.move_back();
	// }

	if(keyboard.isdown(Keycode::A)) {
		camera.move_left();
	} else if(keyboard.isdown(Keycode::D)) {
		camera.move_right();
	}

	if(keyboard.isdown(Keycode::LSHIFT)) {
		camera.fly_down();
	} else if(keyboard.isdown(Keycode::SPACE)) {
		camera.fly_up();
	}


	// ZOOM //
	if(mouse.scroll == Scroll::UP) {
		camera.zoom_in(5.0f);
	} else if(mouse.scroll == Scroll::DOWN) {
		camera.zoom_out(5.0f);
	}
}



int main() {
	Window window = Window("Hello Dynastinae", 800, 600, true, true);

	// NOTE -- Path is relative from where you run the executable (not where the executable is)
	Texture hideri = Texture("tests/assets/images/hideri.jpg", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture kuromi = Texture("tests/assets/images/kuromi.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture brick = Texture("tests/assets/images/brick.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);

	// MUSIC - Play only one at the channel
	// SOUND - Can play multple at the same channel
	Audio mp3 = Audio("tests/assets/sounds/sound.mp3", AudioType::SOUND);
	Audio wav = Audio("tests/assets/sounds/sound2.wav", AudioType::MUSIC);

	Font font = Font("tests/assets/fonts/msgothic.ttf", "FPS: 0", 24, { 255 }); // Path, Text, Size, Color
	font.set_position({ 10.0f, 10.0f }); // This won't change, so is a good idea to set here

	// Scenes
	Scene2D scene2d = Scene2D(window);
	Camera camera = Camera(window, 70.0f, 100.0f); // 3D environment
	Scene3D scene3d = Scene3D(camera);             // 3D render

	bool can_move = false; // Used for camera movement
	float rotation = 0.0f;
	uint32 start_time = window.time();

	while(window.is_open()) {
		// Clear screen with color
		window.clear({ 255, 127, 255 });

		// Process all frame events
		window.process_events();

		// If click to close window
		if(window.trigger_event(Event::QUIT)) {
			window.close();
		}

		// Handle some events
		process_keyboard(window, *window.keyboard());
		process_camera(window, *window.keyboard(), *window.mouse(), camera, can_move);

		// Draw 2D Shapes
		scene2d.draw_shapes(
			Triangle().set_texture(&brick).set_position({ 100.0f, 100.0f })
				.set_size(100.0f).set_angle(50.0f).set_color({ 0, 255, 0 }),

			Rectangle().set_position({ 500.0f, 370.0f }).set_size(100.0f).set_angle(rotation)
				.set_color(Color::from_hex(0xCA1773))
		);

		scene3d.draw_shapes(
			Pyramid().set_texture(&hideri)
				.set_position({ 0.0f, 0.0f, -3.0f })
				.set_scale(2.0f)
				.set_angle(rotation)
				.set_axis({ 0, 1, 0 }),

			Pyramid().set_color(Color::from_hex(0xca1773))
				.set_position({ 5.0f, 0.0f, -3.0f })
				.set_angle(rotation)
				.set_axis({ 0, -1, 0 }),

			Cube().set_texture(&kuromi)
				.set_position({ 3.0f, 2.0f, 1.0f })
				.set_angle(rotation)
				.set_axis({ 1, 1, 1 }),

			Cube().set_texture(&brick)
				.set_position({ 5.0f, -2.0f, 4.0f })
				.set_angle(rotation)
				.set_axis({ 0, 1, -1 })
		);

		// Update FPS each second
		uint32 current_time = window.time();
		if(current_time - start_time >= 1000) {
			font.set_text("FPS: " + std::to_string(window.fps()));
			start_time = window.time();
		}

		// Draw fps
		scene2d.draw_font(font);

		// Rotate
		rotation += 1.0f;
		if(rotation > 360.0f) {
			rotation = 0.0f;
		}

		// Swap buffers and all updates needed on frame end
		window.swap_buffers();
	}

	// Check for any OpenGL error
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		std::cout << "~> OpenGL error code: " << err << std::endl;
	}
}
