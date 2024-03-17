#include "../../include/types/audio.hpp"
#include "../../include/utils/string.hpp"

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

// loops -> -1 to repeat forever
void Audio::play(const short loops) const {
	if(this->sound != nullptr) {
		Mix_PlayChannel(-1, this->sound, (loops > 0) ? loops - 1 : loops);
	} else {
		Mix_PlayMusic(this->music, loops);
	}
}
