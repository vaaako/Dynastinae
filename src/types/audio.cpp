#include "Dynastinae/types/audio.hpp"
#include "Dynastinae/utils/string.hpp"

#include <SDL2/SDL.h>
#include <stdexcept>

Audio::Audio(const std::string& path, const bool ismusic) : path(path), ismusic(ismusic) {
	const std::string extension = String::file_extension(path);
	if(!(extension == "wav" || extension == "ogg" || extension == "flac" || extension == "mp3")) {
		Mix_CloseAudio();
		SDL_Quit();
		throw std::invalid_argument("Failed to load audio \"" + path + "\"\n~> Supported extensions are: WAV, OGG, FLAC and MP3");
	}

	// Init
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
		Mix_CloseAudio();
		SDL_Quit();
		throw std::runtime_error("Failed to init audio " + path + "\n~> " + SDL_GetError());
	}


	if(ismusic) {
		this->music = Mix_LoadMUS(path.c_str());
	} else {
		this->sound = Mix_LoadWAV(path.c_str());
	}
}

// != 0 -> is playing
bool Audio::isplaying() const {
	return (Mix_Playing(-1) != 0);
}

void Audio::set_volume(const uint8 volume) {
	if(volume > MIX_MAX_VOLUME) {
		this->volume = MIX_MAX_VOLUME;
	}

	this->volume = volume;

	// If is music
	if(this->music != nullptr) {
		Mix_VolumeMusic(volume);
		return;
	}

	// If is sound
	Mix_Volume(0, volume);
}

void Audio::set_half_volume() {
	this->volume = static_cast<uint8>(this->volume / 2);

	// If is music
	if(this->music != nullptr) {
		Mix_VolumeMusic(this->volume / 2);
		return;
	}

	// If is sound
	Mix_Volume(0, this->volume / 2);
}

void Audio::set_half_max_volume() {
	this->volume = MIX_MAX_VOLUME / 2;

	// If is music
	if(this->music != nullptr) {
		Mix_VolumeMusic(this->volume);
		return;
	}

	// If is sound
	Mix_Volume(0, this->volume);
}


// loops -> -1 to repeat forever
void Audio::play(const int8 loops) const {
	if(this->sound != nullptr) {
		Mix_PlayChannel(-1, this->sound, (loops > 0) ? loops - 1 : loops);
	} else {
		Mix_PlayMusic(this->music, loops);
	}
}
