#pragma once

#include "../types/color.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_ttf.h>

#include <GL/glew.h>

#include <algorithm>
#include <string>
#include <vector>


enum class Event {
	NOTHING = 0,
	KEYDOWN = 768,
	KEYUP = 769,
	MOUSEDOWN = 1025,
	MOUSEUP = 1026,
	MOUSEMOTION = 1024,
	QUIT = 256
};

// Global window so i can acess from anywhere??

class Window {
	public:
		Window(const std::string& title, const int width, const int height, const bool vsync = true, const bool debug_info = false);
		~Window() {
			// Delete window
			SDL_Log("Window %d destroyed", SDL_GetWindowID(this->window));
			SDL_GL_DeleteContext(this->glContext);
			SDL_DestroyWindow(this->window);

			// Close all
			IMG_Quit();
			SDL_CloseAudio();
			TTF_Quit();
			SDL_Quit();

			delete this->keyboard_handler;
			delete this->mouse_handler;
		}

		// This method is intended to only run once per frame
		void process_events();

		/**
		 * WINDOW PROCESS */
		// Runs in the frame beggining
		inline bool is_open() {
			this->last_update = SDL_GetTicks();
			this->frame_count++;

			return this->window_open;
		}

		// Runs in the frame ending
		inline void swap() {
			this->frame_events.clear(); // Clear events
			SDL_GL_SwapWindow(this->window);
		}

		inline void clear(const Color& color) {
			glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		/**
		 * GETTERS */
		inline SDL_Window* get_reference() const {
			return this->window;
		}

		inline Keyboard* keyboard() const {
			return this->keyboard_handler;
		}

		inline Mouse* mouse() const {
			return this->mouse_handler;
		}

		inline std::string get_title() const {
			return this->title;
		}

		inline int get_width() const {
			return this->width;
		}

		inline int get_height() const {
			return this->height;
		}

		// Check if event in array is not 0, if not, event is activated
		inline bool trigger_event(SDL_EventType event) {
			return std::find(this->frame_events.begin(), this->frame_events.end(), event) != this->frame_events.end();
		}

		/**
		 * SETTERS */
		inline void close() {
			this->window_open = false;
		}

		inline void set_title(const std::string& title) {
			this->title = title.c_str();
			SDL_SetWindowTitle(this->window, title.c_str());
		}

		// TODO -- Put on mouse struct, but how? how can i avoid circular? wjjjj
		inline void set_cursor_position(const unsigned int x, const unsigned int y) {
			if(x > this->width || y > this->height) {
				return;
			}

			SDL_WarpMouseInWindow(this->window, x, y);
			this->mouse_handler->set_position(x, y);
		}


		/**
		 * TIMER */
		inline unsigned int time() {
			return SDL_GetTicks();
		}

		inline double dt(const float time = 1000.0f) const {
			// CURRENT - LAST to seconds
			return static_cast<double>(SDL_GetTicks() - this->last_update) / time;
		}

		inline float fps() {
			unsigned int current_time = SDL_GetTicks();

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


		/**
		* STATIC */
		static inline int static_width() {
			int width;
			SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &width, NULL);
			return width;
		}

		static inline int static_height() {
			int height;
			SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), NULL, &height);
			return height;
		}

	private:
		// Window information
		std::string title;
		int width;
		int height;
		bool window_open = true;

		std::vector<uint> frame_events;

		// SDL2
		SDL_Window* window;
		SDL_GLContext glContext;

		// FPS
		unsigned int start_time = SDL_GetTicks();
		unsigned int last_update = 0;
		int frame_count = 0;
		float FPS = 0.0f;

		// KEYS
		// Pointers because it has a getter method
		Keyboard* keyboard_handler = new Keyboard();
		Mouse* mouse_handler = new Mouse(); // To not have the same name as the "mouse" function

		void init_sdl() const;
};
