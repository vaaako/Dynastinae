#include "../../include/window/window.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

Window::Window(const std::string& title, const int width, const int height, const bool vsync, const bool debug_info)
	: title(title), width(width), height(height) {
	const bool init = this->init_window();

	// Check if was inited succesfully
	if(!init) {
		SDL_Log("Could not init SDL: %s", SDL_GetError());
		SDL_Quit();
		return;
	}

	// Make window
	this->window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,

		width, height,

		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	if(!this->window) {
		SDL_Log("Unable to create a window SDl: %s" , SDL_GetError());
		SDL_Quit();
		return;
	}

	// Load OpenGL
	this->glContext = SDL_GL_CreateContext(window);
	// if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
	// 	SDL_Log("Failed to initalize GLAD:  %s" , SDL_GetError());
	// 	SDL_DestroyWindow(window);
	// 	SDL_Quit();
	// 	return;
	// }


	if (SDL_GL_SetSwapInterval(vsync) < 0) {
		SDL_Log("Failed to enable VSync: %s", SDL_GetError());
		return;
	}
	// SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED );

	// Initialize GLEW
	// glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK) {
		SDL_Log("Failed to initialize GLEW: %s", glewGetErrorString(err));
		SDL_GL_DeleteContext(this->glContext);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
		return;
	}

	glViewport(0, 0, width, height);

	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Non-premultiplied alpha

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	if(debug_info) {
		SDL_Log("OpengGL Loaded!");
		SDL_Log("GLAD Version: %s", glGetString(GL_VERSION));
		SDL_Log("GLEW Version: %s", glGetString(GLEW_VERSION));
		SDL_Log("Vendor: %s", glGetString(GL_VENDOR));
		SDL_Log("Renderer: %s", glGetString(GL_RENDERER));
		SDL_Log("Viewport: %dx%d \n==========\n", width, height);
	}
}


bool Window::init_window() const {
	// Init SDL
	// SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		return false;
	}

	// Initialize SDL_image
	int img_flags = IMG_INIT_JPG;
	if(!(IMG_Init(img_flags) & img_flags)) {
		SDL_Log("IMG_Init Error: %s", IMG_GetError());
		return false;
	}

	return true;
}

Event Window::process_event() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return Event::QUIT;

			/**
			 * KEYBOARD EVENT */
			case SDL_KEYDOWN: {
				std::cout << "Keydown: " << event.key.keysym.sym << std::endl;
				// std::cout << "Repeat: " << (int)event.key.repeat << std::endl;
				keybrd.keydown(event.key.keysym.sym, (bool)event.key.repeat);
				return Event::KEYDOWN;
			}

			case SDL_KEYUP: {
				std::cout << "Keyup: " << event.key.keysym.sym << std::endl;
				keybrd.keyup(event.key.keysym.sym);
				return Event::KEYUP;
			}

			/**
			 * MOUSE EVENT */
			case SDL_MOUSEBUTTONDOWN: {
				// std::cout << "Mouse Click Axis: " << event.button.x << ":" << event.button.y << std::endl;
				// std::cout << "Mouse Clicks: " << (int)event.button.clicks << std::endl;
				SDL_MouseButtonEvent mouse_event = event.button;
				rat.btndown(mouse_event.x, mouse_event.y, mouse_event.button, mouse_event.clicks);
				return Event::MOUSEDOWN;
			}

			case SDL_MOUSEBUTTONUP: {
				rat.btnup(event.button.button);
				return Event::MOUSEUP;
			}

			case SDL_MOUSEMOTION: {
				// std::cout << "Mouse Motion: " << event.motion.x << ":" << event.motion.y << std::endl;
				SDL_MouseMotionEvent mouse_event = event.motion;
				rat.motion(mouse_event.x, mouse_event.y, mouse_event.xrel, mouse_event.yrel);
				return Event::MOUSEMOTION;
			}

			/**
			 * WINDOW EVENT */
			/*
			case SDL_WINDOWEVENT: {
				switch (event.window.event) {
					// Focus lost
					case SDL_WINDOWEVENT_FOCUS_LOST:
						break;

					// Mouse leave window
					case SDL_WINDOWEVENT_LEAVE:
						break;

					default:
						break;
				}
				break;
			}
			*/


			default:
				return Event::NOTHING;
		}
	}

	return Event::NOTHING;
}
