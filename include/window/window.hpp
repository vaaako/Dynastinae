#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_video.h>
#include <GL/glew.h>
#include <string>


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
			SDL_GL_DeleteContext(this->glContext);
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

		inline void clear(const float r, const float g, const float b, const float o = 1.0f) {
			// Rendering
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

		inline int get_width() {
			return this->width;
		}

		inline int get_height() {
			return this->height;
		}

		static inline int get_static_width() {
			int width;
			SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &width, NULL);
			return width;
		}

		static inline int get_static_height() {
			int height;
			SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), NULL, &height);
			return height;
		}
	private:
		SDL_Window* window;
		SDL_GLContext glContext;
		bool window_open = true;
		const int width;
		const int height;

		// KEYS
		Keyboard keybrd = Keyboard();
		Mouse rat = Mouse(); // To not have the same name as the "mouse" function


		bool init_window() const;
};
