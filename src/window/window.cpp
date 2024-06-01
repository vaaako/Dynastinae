#include "Dynastinae/window/window.hpp"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

#include <stdexcept>

Window::Window(const std::string& title, const uint32 width, const uint32 height, const bool vsync, const bool debug_info)
	: title(title), width(width), height(height) {

	/**
	 * INIT SDL */
	// SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("~> Failed to init video module " + std::string(SDL_GetError()));
	}

	if(SDL_Init(SDL_INIT_AUDIO) != 0) {
		throw std::runtime_error("~> Failed to init audio module " + std::string(SDL_GetError()));
	}

	if(TTF_Init() != 0) {
		throw std::runtime_error("~> Failed to init font module " + std::string(SDL_GetError()));
	}


	// TODO -- do I really need to init IMG like this?
	// Initialize SDL_image
	int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(!(IMG_Init(img_flags) & img_flags)) {
		throw std::runtime_error("~> Failed to init image module " + std::string(IMG_GetError()));
	}

	// Make window
	this->window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,

		static_cast<int>(width), static_cast<int>(height),

		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);

	if(!this->window) {
		SDL_Log("Unable to create a window SDl: %s" , SDL_GetError());
		SDL_Quit();
		return;
	}

	// Load OpenGL
	this->glContext = SDL_GL_CreateContext(window);

	if (SDL_GL_SetSwapInterval(vsync) < 0) {
		SDL_Log("Failed to enable VSync: %s", SDL_GetError());
		return;
	}


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



	/**
	 * CONFIGURE OPENGL */

	// Init Viewport
	glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));

	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Non-premultiplied alpha

	// Enables Depth
	glEnable(GL_DEPTH_TEST);

	// Show debug info
	if(debug_info) {
		SDL_Log("OpengGL Loaded!");
		SDL_Log("GL Version: %s", glGetString(GL_VERSION));
		SDL_Log("Vendor: %s", glGetString(GL_VENDOR));
		SDL_Log("Renderer: %s", glGetString(GL_RENDERER));
		SDL_Log("Viewport: %dx%d \n==========\n", width, height);
	}
}

float Window::fps() {
	uint32 current_time = SDL_GetTicks();

	// Update every second
	if(current_time - start_time >= 1000) {
		// Calc FPS
		this->FPS = static_cast<float>(frame_count) / (static_cast<float>(current_time - start_time) / 1000.0f);

		// Reset
		this->frame_count = 0;
		this->start_time = current_time; // Update timer
	}

	return this->FPS;
}

void Window::set_cursor_position(const int x, const int y) {
	if(x > (int)(this->width) || y > (int)(this->height)) {
		return;
	}

	SDL_WarpMouseInWindow(this->window, x, y);
	this->mouse_handler->set_position(x, y);
}

void Window::process_events() {
	this->last_update = SDL_GetTicks();
	this->frame_count++;

	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		// Store all events in this frame
		this->frame_events.emplace_back(static_cast<uint32>(event.type));

		// Handle events necessary to the engine working
		switch (event.type) {
			/**
			 * KEYBOARD EVENTS */
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				this->keyboard_handler->handle_event(event);
				break;

			/**
			 * MOUSE EVENTS */
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEMOTION:
				this->mouse_handler->handle_event(event);
				break;

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
				break;
		}
	}
}

