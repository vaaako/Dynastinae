#include "../include/window/window.hpp"
#include "../include/shapes/renderer/renderer2d.hpp"
#include "../include/shapes/renderer/camera.hpp"
#include "../include/types/audio.hpp"
#include "../include/types/font.hpp"

#include <iostream>


// https://wiki.libsdl.org/SDL2/SDL_Scancode
void process_keyboard(Window& window, Keyboard& keyboard) {
	// 27 - ESC
	// if(keyboard.down == 27 || keyboard.down == SDLK_ESCAPE) {
	// 	std::cout << "Closing" << std::endl;
	// 	window.close();
	// }
	//
	// Enter
	// if(keyboard.down == SDLK_RETURN) {}

	if(keyboard.isdown(Keycode::ESCAPE)) {
		std::cout << "TRUE CLOSING" << std::endl;
		window.close();
	}
}


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


/**
 * TODO --
 * - Custom vertex colors for 2D?
 *   + Later
 *   + Add to vertex attrib 2 on shape VBO and check if is to use on shape instance
 *    
 * - .obj: When creating a OBJ `OBJ obj = Obj()` -> `renderer3d.draw_obj(obj)`. This makes a new VAO and VBO of that obj
 *    
 *    
 * - [ ] Use Vector2f and Vector3f instead of glm versions
 * - [ ] Unify shader and shader_texture somehow
 * - [X] Code keyboard enums
 * - [ ] More window events
 * - [ ] Resizing support
 * - [ ] Multiple events support
 * - [ ] Structs to .cpp
 *    
 * - https://github.com/vaaako/Vakraft/blob/main/src/main/java/com/magenta/main/Game.java#L121
 * */


// WARNING -- Current problem: Camera works, but not smooth, because window only handles one event per frame
// Pensar em algum jeito de por SDL_PollEvent sem ter que dar return, porque o return que faz executar só um por frame
// Uma solução que eu vi foi por em um vector, só não sei o que fazer depois disso
// Mas a ideia é evitar o return, porque isso que faz os eventos serem executados só um por frame
//    
// Na verdade eu não preciso retornar nada, já que os eventos de keyboard e mouse tem handle da própria framework
// Mas por que preciso do vector?


/** INFO CURRENTLY WORKING ON
 * 
 * - Make camera cube also use matrix method
 * - Fix camera movement
 * - Fix camera methods and variables
 * - Make own events enums like i did with keyboard
 * */

int main() {
	Window window = Window("Hello Dynastinae", 800, 600, true, true);

	Texture* texture = new Texture("src/texture.jpg", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture* kuromi = new Texture("src/kuromi.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);
	Texture* brick = new Texture("src/brick.png", TextureFilter::NEAREST, TextureWrap::MIRRORED);

	// MUSIC - Play only one at the channel
	// SOUND - Can play multple at the same channel
	Audio* mp3 = new Audio("src/sound.mp3", false); // Path, is music
	Audio* wav = new Audio("src/sound2.wav", true);

	Font* font = new Font("src/msgothic.ttf", "FPS: 0", 24, { 255 }); // Path, Text, Size, Color


	Renderer2D renderer = Renderer2D(window);
	Camera camera = Camera(window); // 3D environment


	float rotation = 0.0f;
	unsigned int start_time = window.time();
	while(window.is_open()) {
		window.clear({ 255, 127, 255 });

		window.process_events();
		// std::cout << "Event: " << (int)event << std::endl;

		process_keyboard(window, *window.keyboard());
		move_camera(*window.keyboard(), camera);
		camera.rotate(window, *window.mouse());

		if(window.trigger_event(SDL_QUIT)) {
			window.close();
		}

		// renderer.triangle(brick, 100.0f, 100.0f, 100.0f, 50.0f, Color(0, 255, 0));
		// renderer.rectangle(brick, 50.0f, 100.0f, 200.0f, 200.0f);
		//
		// renderer.triangle(550.0f, 350.0f, 100.0f, rotation);
		// renderer.rectangle(500.0f, 370.0f, 200.0f, 200.0f, Color::from_hex(0xCA1773));


		// Don't worry about draw order with 2D, 2D shapes are always above 3D shapes
		camera.pyramid(texture, -1.0f, -1.0f, -7.0f, rotation, { 0, 255, 0 });
		// renderer3d.cube(kuromi, 1.0f, 1.0f, -8.0f, rotation, { 255, 255, 0 });


		// Update FPS each seconds
		unsigned int current_time = window.time();
		if(current_time - start_time >= 1000) {
			font->set_text("FPS: " + std::to_string(window.fps()));
			start_time = window.time();
		}
		renderer.draw_font(*font, 10.0f, 10.0f);

		rotation += 1.0f;
		if(rotation > 360.0f) {
			rotation = 0.0f;
		}


		window.swap();
	}

	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		std::cout << "~> OpenGL error code: " << err << std::endl;
	}
}
