#pragma once

#include <string>
#include <SDL2/SDL_mixer.h>

struct Audio {
	const std::string path;
	const bool ismusic;
	unsigned short volume = MIX_MAX_VOLUME;

	Mix_Music* music = nullptr;
	Mix_Chunk* sound = nullptr;

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

	void play(const short loops = 0) const;

	inline bool isplaying() const {
		if(Mix_Playing(-1) != 0) return true;
		else return false;
	}

	inline void set_volume(unsigned short volume) {
		if(volume > MIX_MAX_VOLUME) {
			volume = MIX_MAX_VOLUME;
		}

		this->volume = volume;

		if(this->music != nullptr) {
			Mix_VolumeMusic(volume);
			return;
		}

		Mix_Volume(0, volume);
	}

	inline void set_half_volume() {
		this->volume = MIX_MAX_VOLUME;

		if(this->music != nullptr) {
			Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
			return;
		}

		Mix_Volume(0, MIX_MAX_VOLUME / 2);
	}
};
