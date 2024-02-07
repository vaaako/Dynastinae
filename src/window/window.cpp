#include "../../include/window/window.hpp"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

Window::Window(const std::string& title, const int width, const int height, const bool show_info)
	: width(width), height(height) {
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
	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_Log("Failed to initalize GLAD:  %s" , SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return;
	}

	glViewport(0, 0, width, height); // Not really necessary

	if(show_info) {
		SDL_Log("OpengGL Loaded! \nVersion: %s \nVendor: %s \nRenderer: %s", glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));
		SDL_Log("Viewport: %dx%d", width, height);
	}
}


bool Window::init_window() const {
	// Init SDL
	// SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	return true;
}

#include <iostream>

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
				mse.btndown(mouse_event.x, mouse_event.y, mouse_event.button, mouse_event.clicks);
				return Event::MOUSEDOWN;
			}

			case SDL_MOUSEBUTTONUP: {
				mse.btnup(event.button.button);
				return Event::MOUSEUP;
			}

			case SDL_MOUSEMOTION: {
				// std::cout << "Mouse Motion: " << event.motion.x << ":" << event.motion.y << std::endl;
				SDL_MouseMotionEvent mouse_event = event.motion;
				mse.motion(mouse_event.x, mouse_event.y, mouse_event.xrel, mouse_event.yrel);
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
