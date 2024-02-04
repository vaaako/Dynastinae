#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <string>

#include "../../libs/glad/glad.h"

#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"


enum class Event {
	NOTHING,
	KEYDOWN,
	KEYUP,
	MOUSEDOWN,
	MOUSEUP,
	MOUSEMOTION,
	QUIT
};

class Window {
	public:
		Window(const std::string& title, const int width, const int height, const bool show_info = false);
		~Window() {
			SDL_Log("Window %d destroyed", SDL_GetWindowID(this->window));
			SDL_GL_DeleteContext(glContext);
			SDL_DestroyWindow(this->window);
			SDL_Quit();
		}

		Event process_event();

		inline SDL_Window* get_reference() const {
			return this->window;
		}
		
		/**
		 * WINDOW PROCESS */
		inline bool is_open() const {
			return this->window_open;
		}

		inline void clear(const float r, const float g, const float b, const float o) {
			// Rendering
			// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClearColor(r, g, b, o);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		inline void swap() {
			// Swap the buffers
			SDL_GL_SwapWindow(this->window);
		}

		inline void close() {
			this->window_open = false;
		}

		/**
		 * GETTERS */
		inline Keyboard keyboard() {
			return this->keybrd;
		}

		/**
		 * VIRTUAL */
		// virtual void keydown(const int code) = 0;
	private:
		SDL_Window* window;
		SDL_GLContext glContext;
		bool window_open = true;

		// KEYS
		Keyboard keybrd = Keyboard();
		Mouse mse = Mouse();


		bool init_window() const;
};
