#pragma once

#include <string>
#include <SDL2/SDL_mixer.h>
#include "../types/default.hpp"

struct Audio {
	const std::string path;
	const bool ismusic;
	uint8 volume = MIX_MAX_VOLUME;

	Mix_Music* music = nullptr;
	Mix_Chunk* sound = nullptr;

	// WARNING -- Possible memory leak?
	Audio(const std::string& path, const bool ismusic = false);
	~Audio() {
		// if(sound != nullptr) {
		// 	Mix_FreeChunk(this->sound);
		// 	return;
		// }
		// Mix_FreeMusic(this->music);

		Mix_FreeChunk(this->sound);
		Mix_FreeMusic(this->music);
	}

	void play(const int8 loops = 0) const;

	bool isplaying() const;
	void set_volume(const uint8 volume);
	void set_half_volume();
	void set_half_max_volume();
};
