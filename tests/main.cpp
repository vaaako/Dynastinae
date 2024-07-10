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

// TODO -- Making a circle -- https://github.com/vaaako/Vakraft/blob/main/src/main/java/com/magenta/game/Aim.java
int main() {
	Window window = Window("Hello Dynastinae", 800, 600, true, true);

	// NOTE -- Path is relative from where you run the executable (not where the executable is)
	Texture hideri = Texture("tests/assets/images/hideri.jpg", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture kuromi = Texture("tests/assets/images/kuromi.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture brick = Texture("tests/assets/images/brick.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture spot_texture = Texture("tests/assets/images/spot_texture.png");

	// MUSIC - Play only one at the channel
	// SOUND - Can play multple at the same channel
	Audio mp3 = Audio("tests/assets/sounds/sound.mp3", AudioType::SOUND);
	Audio wav = Audio("tests/assets/sounds/sound2.wav", AudioType::MUSIC);

	Font font = Font("tests/assets/fonts/msgothic.ttf", "FPS: 0", 24, { 255 }); // Path, Text, Size, Color
	font.set_position({ 10.0f, 10.0f }); // This won't change, so is a good idea to set here

	Mesh teapot = Mesh("tests/assets/objs/teapot.obj");
	Mesh cow = Mesh("tests/assets/objs/cow.obj");
	Mesh spot = Mesh("tests/assets/objs/spot.obj");
	Mesh bunny = Mesh("tests/assets/objs/stanford-bunny.obj");
	Mesh armadillo = Mesh("tests/assets/objs/armadillo.obj");
	Mesh dragon = Mesh("tests/assets/objs/xyzrgb_dragon.obj");

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
		// scene2d.draw_shapes(
		// 	Triangle().set_texture(&brick).set_position({ 100.0f, 100.0f })
		// 		.set_size(100.0f).set_angle(50.0f).set_color({ 0, 255, 0 }),
		//
		// 	Rectangle().set_position({ 500.0f, 370.0f }).set_size(100.0f).set_angle(rotation)
		// 		.set_color(Color::from_hex(0xCA1773))
		// );

		// TODO -- set_scale not working for custom models
		scene3d.draw_shapes(
			teapot.set_color(Color::from_hex(0xca1773))
					.set_position({ -15.0f, 0.0f, -10.0f })
					.set_angle(rotation)
					.set_axis({ 0, -1, 0 }),

			cow.set_color(Color::from_hex(0xffe189))
					.set_position({ -15.0f, 0.0f, -25.0f })
					.set_angle(rotation)
					.set_axis({ 0, 1, 0 }),

			spot.set_texture(&spot_texture)
					.set_position({ -15.0f, 0.0f, -40.0f })
					.set_angle(rotation)
					.set_axis({ 0, 1, 0 }),

			bunny.set_color(Color::from_hex(0xffe189))
					.set_size(30.0f) // Bunny
					.set_position({ -15.0f, 0.0f, -55.0f })
					.set_angle(rotation)
					.set_axis({ 0, 1, 0 }),

			armadillo.set_color(Color::from_hex(0xffe189))
					.set_size(0.075f)
					.set_position({ -15.0f, 0.0f, -70.0f })
					.set_angle(rotation)
					.set_axis({ 0, -1, 0 }),

			dragon.set_color({ 0, 255, 0 })
					.set_size(0.075f)
					.set_position({ -15.0f, 0.0f, -85.0f })
					.set_angle(rotation)
					.set_axis({ 0, 1, 0 }),

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
				.set_axis({ 0, 1, -1 }),
			

			/*
			 * EXPLAINING SIZES
			 */
			// Cubes has 1.0f of size
			// Since this is the case, scaling to 2.0f is the same that setting the size to 2.0f
			// But if first set the size to 2.0f and then the scale 2.0f, the size becomes 4.0f
			Cube().set_texture(&brick)
				// Scales to size 4.0f
				.set_size(2.0f)
				.set_scale(2.0f)

				.set_position({ 0.0f, 0.0f, -20.0f }),

			// Since the first cube size is 1.0f, 2.0f places this cube right on the limit of the first cube
			// This .1f is just to show the offset between
			Cube().set_texture(&brick)
				.set_position({ 5.1f, 0.0f, -20.0f }), // For 4.0f size
				// .set_position({ 2.1f, 0.0f, -20.0f }), // For 1.0f size

			// Pyramid size is also 1.0f
			Pyramid().set_texture(&brick)
				.set_position({ 0.0f, 5.5f, -20.0f }),

			Pyramid().set_texture(&brick)
				.set_position({ 2.1f, 5.5f, -20.0f }),

			// You can set size to some specific axis
			// For example, if you set the cube axis Z size to 0.0f, you make a square
			Cube().set_texture(&brick)
				.set_position({ 10.0f, 0.0f, -10.0f })
				.set_size({ 1.0f, 1.0f, 0.0f })
				// Rotating a bit to show the effect
				.set_angle(20.0f)
				.set_axis({ 0, 10, 0 }),


			// You can also set the initial size, angle and etc on cube creation
			// Cube(&brick, { 0.0f, 0.0f, -15.0f }, 2.0f, 10.0f) // Texture, position, size, angle
			// Same to other shapes
			

			// A little house!
			Cube().set_texture(&kuromi)
				.set_position({ -10.0f, 0.0f, 0.0f }),
			Pyramid().set_texture(&brick)
				.set_position({ -10.0f, 2.0f, 0.0f }),

			// Pulsing cube
			Cube().set_texture(&kuromi)
				.set_position({ 10.0f, 0.0f, 0.0f })
				.set_size(std::sin(rotation / 10.0f))
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
